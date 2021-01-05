#ifndef STORAGE_POOL_H
#define STORAGE_POOL_H

#include "../ast.h"
#include "../core/AstSwitchStatement.h"
#include "../core/AstWhileStatement.h"
#include "../core/AstSwitchBlockStatement.h"

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes { // Open namespace Jikes block
#endif

//
// This Storage pool is similar to dynamic arrays (class Tuple). The
// difference is that instead of a Next() function we have an Alloc(size_t)
// function. The value of the size_t argument represents the size of the
// object to allocate. The allocated memory is guaranteed to be
// zero-initialized.
//
// All AST nodes for a given parse should be allocated from the same storage
// pool, so they have a placement new operator that requires a StoragePool.
// You should never delete an AST object, as all resources they allocate come
// from the same pool. Instead, to reclaim memory when processing is complete,
// simply delete the underlying storage pool.
//
class StoragePool
{
public:
    typedef void* Cell;

    inline size_t Blksize() { return 1U << log_blksize; }

private:
    Cell** base;
    unsigned base_size; // number of segment slots in base
    unsigned base_index; // index of current non-full segment
    unsigned offset; // offset to next free pointer in base[base_index]

    unsigned log_blksize; // log2(words per segment)
    unsigned base_increment; // number of segment slots to add when growing

    //
    // Allocate another block of storage for the storage pool. block_size
    // allows the creation of larger than normal segments, which are rare,
    // but are sometimes requested by AstArray.
    //
    void AllocateMoreSpace(size_t block_size = 0)
    {
        //
        // This advances base_index to the next slot unless this is the first
        // allocation. Then it allocates a segment to live in that slot.
        // The offset field should only be 0 after construction or after a
        // reset, when base_index should stay at 0.  All other times, offset
        // is nonzero, so we allocate advance base_index.
        //
        assert(offset ? base != NULL : ! base_index);
        if (offset)
            base_index++;
        if (base_index == base_size)
        {
            unsigned old_base_size = base_size;
            Cell** old_base = base;
            base_size += base_increment;
            base = new Cell*[base_size];
            if (old_base)
            {
                memcpy(base, old_base, old_base_size * sizeof(Cell*));
                delete [] old_base;
            }
            memset(base + old_base_size, 0, base_increment * sizeof(Cell*));
        }
        if (block_size)
        {
            assert(block_size > Blksize());
            delete [] base[base_index];
            base[base_index] = new Cell[block_size];
        }
        else if (! base[base_index])
        {
            block_size = Blksize();
            base[base_index] = new Cell[block_size];
        }
        memset(base[base_index], 0, block_size * sizeof(Cell));
    }

public:
    //
    // Constructor of a storage pool. The parameter is the number of tokens
    // which the AST tree will contain.
    //
    StoragePool(unsigned num_tokens)
        : base(NULL)
        , base_size(0)
        , base_index(0)
        , offset(0)
    {
        //
        // Make a guess on the size that will be required for the ast
        // based on the number of tokens. On average, we have about 1 node
        // to 2 tokens, but about 10 words (40 bytes) per node. We add some
        // fudge factor to avoid reallocations, resulting in num_tokens * 8.
        //
        unsigned estimate = num_tokens << 3;

        //
        // Find a block of size 2**log_blksize that is large enough
        // to satisfy our estimate.
        //
        for (log_blksize = 8;
             (1U << log_blksize) < estimate && log_blksize < 31;
             log_blksize++)
            ;

        if (log_blksize < 13) // estimate is < 2**(13+2) == 32k
        {
            base_increment = 1U << (log_blksize - 8);
            log_blksize = 8; // fragment in 2**(8+2) == 1k chunks
        }
        else if (log_blksize < 17) // estimate is < 2**(17+2) == 512k
        {
            base_increment = 1U << (log_blksize - 10);
            log_blksize = 10; // fragment in 2**(10+2) == 4k chunks
        }
        else // estimate is >= 512k, which is rare
        {
            base_increment = 1U << (log_blksize - 12);
            log_blksize = 12; // fragment in 2**(12+2) == 16k chunks
        }

        //
        // Double the size of the base and add an extra margin to avoid
        // reallocating the base, especially for things like Cloning.
        //
        base_increment += base_increment + 3;
    }

    //
    // Destructor of a storage pool. This frees the memory of all of the AST
    // nodes allocated in this pool.
    //
    ~StoragePool()
    {
        if (base)
            for (unsigned i = 0; i <= base_index; i++)
                delete [] base[i];
        delete [] base;
    }

    //
    // Alloc allocates an object of size n in the pool and returns a pointer
    // to it. The memory will be zero-initialized.
    //
    inline void* Alloc(size_t n)
    {
        unsigned chunk_size = (n + sizeof(Cell) - 1) / sizeof(Cell);
        if (chunk_size > Blksize())
        {
            //
            // Handle large requests separately. These are rare, when an
            // AstArray is requested that is larger than a segment. In this
            // case, we allocate the extra large segment in the next free
            // slot, and swap it with the previous segment if that one still
            // had room.
            //
            AllocateMoreSpace(chunk_size);
            Cell result = base[base_index];
            if (base_index)
            {
                Cell* temp = base[base_index];
                base[base_index] = base[base_index - 1];
                base[base_index - 1] = temp;
            }
            return result;
        }
        if (! base || offset + chunk_size > Blksize())
        {
            //
            // Here, we overflow the current segment, but fit in a normal
            // next segment.
            //
            AllocateMoreSpace();
            offset = 0;
        }
        Cell result = base[base_index] + offset;
        offset += chunk_size;
        return result;
    }

    //
    // This function is used to reset the Storage pool. This action
    // automatically invalidates all objects that had been allocated in the
    // pool. At least, YOU should assume it does!!!
    //
    inline void Reset()
    {
        base_index = 0;
        offset = 0;
    }

    // ********************************************************************

    inline VariableSymbolArray* NewVariableSymbolArray(unsigned size = 0)
    {
        return new (Alloc(sizeof(VariableSymbolArray)))
            VariableSymbolArray(this, size);
    }

    inline AstListNode* NewListNode()
    {
        return new (this) AstListNode();
    }

    inline AstBlock* NewBlock()
    {
        return new (this) AstBlock(this);
    }

    inline AstName* NewName(TokenIndex token)
    {
        return new (this) AstName(token);
    }

    inline AstPrimitiveType* NewPrimitiveType(Ast::AstKind kind, TokenIndex t)
    {
        return new (this) AstPrimitiveType(kind, t);
    }

    inline AstBrackets* NewBrackets(TokenIndex left, TokenIndex right)
    {
        return new (this) AstBrackets(left, right);
    }

    inline AstArrayType* NewArrayType(AstType* type, AstBrackets* brackets)
    {
        return new (this) AstArrayType(type, brackets);
    }

    inline AstWildcard* NewWildcard(TokenIndex question)
    {
        return new (this) AstWildcard(question);
    }

    inline AstTypeArguments* NewTypeArguments(TokenIndex l, TokenIndex r)
    {
        return new (this) AstTypeArguments(this, l, r);
    }

    inline AstTypeName* NewTypeName(AstName* name)
    {
        return new (this) AstTypeName(name);
    }

    inline AstMemberValuePair* NewMemberValuePair()
    {
        return new (this) AstMemberValuePair();
    }

    inline AstAnnotation* NewAnnotation()
    {
        return new (this) AstAnnotation(this);
    }

    inline AstModifierKeyword* NewModifierKeyword(TokenIndex token)
    {
        return new (this) AstModifierKeyword(token);
    }

    inline AstModifiers* NewModifiers()
    {
        return new (this) AstModifiers(this);
    }

    inline AstPackageDeclaration* NewPackageDeclaration()
    {
        return new (this) AstPackageDeclaration();
    }

    inline AstImportDeclaration* NewImportDeclaration()
    {
        return new (this) AstImportDeclaration();
    }

    inline AstCompilationUnit* NewCompilationUnit()
    {
        return new (this) AstCompilationUnit(this);
    }

    inline AstEmptyDeclaration* NewEmptyDeclaration(TokenIndex t)
    {
        return new (this) AstEmptyDeclaration(t);
    }

    inline AstClassBody* NewClassBody()
    {
        return new (this) AstClassBody(this);
    }

    inline AstTypeParameter* NewTypeParameter(TokenIndex token)
    {
        return new (this) AstTypeParameter(this, token);
    }

    inline AstTypeParameters* NewTypeParameters()
    {
        return new (this) AstTypeParameters(this);
    }

    inline AstClassDeclaration* NewClassDeclaration()
    {
        return new (this) AstClassDeclaration(this);
    }

    inline AstArrayInitializer* NewArrayInitializer()
    {
        return new (this) AstArrayInitializer(this);
    }

    inline AstVariableDeclaratorId* NewVariableDeclaratorId()
    {
        return new (this) AstVariableDeclaratorId();
    }

    inline AstVariableDeclarator* NewVariableDeclarator()
    {
        return new (this) AstVariableDeclarator();
    }

    inline AstFieldDeclaration* NewFieldDeclaration()
    {
        return new (this) AstFieldDeclaration(this);
    }

    inline AstFormalParameter* NewFormalParameter()
    {
        return new (this) AstFormalParameter();
    }

    inline AstMethodDeclarator* NewMethodDeclarator()
    {
        return new (this) AstMethodDeclarator(this);
    }

    inline AstMethodBody* NewMethodBody()
    {
        return new (this) AstMethodBody(this);
    }

    inline AstMethodDeclaration* NewMethodDeclaration()
    {
        return new (this) AstMethodDeclaration(this);
    }

    inline AstInitializerDeclaration* NewInitializerDeclaration()
    {
        return new (this) AstInitializerDeclaration();
    }

    inline AstArguments* NewArguments(TokenIndex left, TokenIndex right)
    {
        return new (this) AstArguments(this, left, right);
    }

    inline AstThisCall* NewThisCall()
    {
        return new (this) AstThisCall();
    }

    inline AstSuperCall* NewSuperCall()
    {
        return new (this) AstSuperCall();
    }

    inline AstConstructorDeclaration* NewConstructorDeclaration()
    {
        return new (this) AstConstructorDeclaration(this);
    }

    inline AstEnumDeclaration* NewEnumDeclaration()
    {
        return new (this) AstEnumDeclaration(this);
    }

    inline AstEnumConstant* NewEnumConstant(TokenIndex t)
    {
        return new (this) AstEnumConstant(t);
    }

    inline AstInterfaceDeclaration* NewInterfaceDeclaration()
    {
        return new (this) AstInterfaceDeclaration(this);
    }

    inline AstAnnotationDeclaration* NewAnnotationDeclaration(TokenIndex t)
    {
        return new (this) AstAnnotationDeclaration(t);
    }

    inline AstLocalVariableStatement* NewLocalVariableStatement()
    {
        return new (this) AstLocalVariableStatement(this);
    }

    inline AstLocalClassStatement* NewLocalClassStatement(AstClassDeclaration* decl)
    {
        return new (this) AstLocalClassStatement(decl);
    }

    inline AstLocalClassStatement* NewLocalClassStatement(AstEnumDeclaration* decl)
    {
        return new (this) AstLocalClassStatement(decl);
    }

    inline AstIfStatement* NewIfStatement()
    {
        return new (this) AstIfStatement();
    }

    inline AstEmptyStatement* NewEmptyStatement(TokenIndex token)
    {
        return new (this) AstEmptyStatement(token);
    }

    inline AstExpressionStatement* NewExpressionStatement()
    {
        return new (this) AstExpressionStatement();
    }

    inline AstSwitchLabel* NewSwitchLabel()
    {
        return new (this) AstSwitchLabel();
    }

    inline AstSwitchBlockStatement* NewSwitchBlockStatement()
    {
        return new (this) AstSwitchBlockStatement(this);
    }

    inline AstSwitchStatement* NewSwitchStatement()
    {
        return new (this) AstSwitchStatement(this);
    }

    inline AstWhileStatement* NewWhileStatement()
    {
        return new (this) AstWhileStatement();
    }

    inline AstDoStatement* NewDoStatement()
    {
        return new (this) AstDoStatement();
    }

    inline AstForStatement* NewForStatement()
    {
        return new (this) AstForStatement(this);
    }

    inline AstForeachStatement* NewForeachStatement()
    {
        return new (this) AstForeachStatement();
    }

    inline AstBreakStatement* NewBreakStatement()
    {
        return new (this) AstBreakStatement();
    }

    inline AstContinueStatement* NewContinueStatement()
    {
        return new (this) AstContinueStatement();
    }

    inline AstReturnStatement* NewReturnStatement()
    {
        return new (this) AstReturnStatement();
    }

    inline AstThrowStatement* NewThrowStatement()
    {
        return new (this) AstThrowStatement();
    }

    inline AstSynchronizedStatement* NewSynchronizedStatement()
    {
        return new (this) AstSynchronizedStatement();
    }

    inline AstAssertStatement* NewAssertStatement()
    {
        return new (this) AstAssertStatement();
    }

    inline AstCatchClause* NewCatchClause()
    {
        return new (this) AstCatchClause();
    }

    inline AstFinallyClause* NewFinallyClause()
    {
        return new (this) AstFinallyClause();
    }

    inline AstTryStatement* NewTryStatement()
    {
        return new (this) AstTryStatement(this);
    }

    inline AstIntegerLiteral* NewIntegerLiteral(TokenIndex token)
    {
        return new (this) AstIntegerLiteral(token);
    }

    inline AstLongLiteral* NewLongLiteral(TokenIndex token)
    {
        return new (this) AstLongLiteral(token);
    }

    inline AstFloatLiteral* NewFloatLiteral(TokenIndex token)
    {
        return new (this) AstFloatLiteral(token);
    }

    inline AstDoubleLiteral* NewDoubleLiteral(TokenIndex token)
    {
        return new (this) AstDoubleLiteral(token);
    }

    inline AstTrueLiteral* NewTrueLiteral(TokenIndex token)
    {
        return new (this) AstTrueLiteral(token);
    }

    inline AstFalseLiteral* NewFalseLiteral(TokenIndex token)
    {
        return new (this) AstFalseLiteral(token);
    }

    inline AstStringLiteral* NewStringLiteral(TokenIndex token)
    {
        return new (this) AstStringLiteral(token);
    }

    inline AstCharacterLiteral* NewCharacterLiteral(TokenIndex token)
    {
        return new (this) AstCharacterLiteral(token);
    }

    inline AstNullLiteral* NewNullLiteral(TokenIndex token)
    {
        return new (this) AstNullLiteral(token);
    }

    inline AstClassLiteral* NewClassLiteral(TokenIndex token)
    {
        return new (this) AstClassLiteral(token);
    }

    inline AstThisExpression* NewThisExpression(TokenIndex token)
    {
        return new (this) AstThisExpression(token);
    }

    inline AstSuperExpression* NewSuperExpression(TokenIndex token)
    {
        return new (this) AstSuperExpression(token);
    }

    inline AstParenthesizedExpression* NewParenthesizedExpression()
    {
        return new (this) AstParenthesizedExpression();
    }

    inline AstClassCreationExpression* NewClassCreationExpression()
    {
        return new (this) AstClassCreationExpression();
    }

    inline AstDimExpr* NewDimExpr()
    {
        return new (this) AstDimExpr();
    }

    inline AstArrayCreationExpression* NewArrayCreationExpression()
    {
        return new (this) AstArrayCreationExpression(this);
    }

    inline AstFieldAccess* NewFieldAccess()
    {
        return new (this) AstFieldAccess();
    }

    inline AstMethodInvocation* NewMethodInvocation(TokenIndex t)
    {
        return new (this) AstMethodInvocation(t);
    }

    inline AstArrayAccess* NewArrayAccess()
    {
        return new (this) AstArrayAccess();
    }

    inline AstPostUnaryExpression* NewPostUnaryExpression(AstPostUnaryExpression::PostUnaryExpressionTag tag)
    {
        return new (this) AstPostUnaryExpression(tag);
    }

    inline AstPreUnaryExpression* NewPreUnaryExpression(AstPreUnaryExpression::PreUnaryExpressionTag tag)
    {
        return new (this) AstPreUnaryExpression(tag);
    }

    inline AstCastExpression* NewCastExpression()
    {
        return new (this) AstCastExpression();
    }

    inline AstBinaryExpression* NewBinaryExpression(AstBinaryExpression::BinaryExpressionTag tag)
    {
        return new (this) AstBinaryExpression(tag);
    }

    inline AstInstanceofExpression* NewInstanceofExpression()
    {
        return new (this) AstInstanceofExpression();
    }

    inline AstConditionalExpression* NewConditionalExpression()
    {
        return new (this) AstConditionalExpression();
    }

    inline AstAssignmentExpression* NewAssignmentExpression(AstAssignmentExpression::AssignmentExpressionTag tag,
                                                            TokenIndex token)
    {
        return new (this) AstAssignmentExpression(tag, token);
    }

    // *********************************************************************

    //
    // Note that CaseElement nodes are always generated. Since they are not
    // Ast nodes they do not need to be marked.
    //
    inline CaseElement* GenCaseElement(unsigned block_index,
                                       unsigned case_index)
    {
        CaseElement* p = new (Alloc(sizeof(CaseElement))) CaseElement();
        p -> block_index = block_index;
        p -> case_index = case_index;
        return p;
    }

    inline AstBlock* GenBlock()
    {
        AstBlock* p = NewBlock();
        p -> generated = true;
        p -> no_braces = true;
        return p;
    }

    inline AstName* GenName(TokenIndex token)
    {
        AstName* p = NewName(token);
        p -> generated = true;
        return p;
    }

    inline AstPrimitiveType* GenPrimitiveType(Ast::AstKind kind, TokenIndex t)
    {
        AstPrimitiveType* p = NewPrimitiveType(kind, t);
        p -> generated = true;
        return p;
    }

    inline AstBrackets* GenBrackets(TokenIndex left, TokenIndex right)
    {
        AstBrackets* p = NewBrackets(left, right);
        p -> generated = true;
        return p;
    }

    inline AstArrayType* GenArrayType(AstType* type, AstBrackets* brackets)
    {
        AstArrayType* p = NewArrayType(type, brackets);
        p -> generated = true;
        return p;
    }

    inline AstWildcard* GenWildcard(TokenIndex question)
    {
        AstWildcard* p = NewWildcard(question);
        p -> generated = true;
        return p;
    }

    inline AstTypeArguments* GenTypeArguments(TokenIndex l, TokenIndex r)
    {
        AstTypeArguments* p = NewTypeArguments(l, r);
        p -> generated = true;
        return p;
    }

    inline AstTypeName* GenTypeName(AstName* type)
    {
        AstTypeName* p = NewTypeName(type);
        p -> generated = true;
        return p;
    }

    inline AstMemberValuePair* GenMemberValuePair()
    {
        AstMemberValuePair* p = NewMemberValuePair();
        p -> generated = true;
        return p;
    }

    inline AstAnnotation* GenAnnotation()
    {
        AstAnnotation* p = NewAnnotation();
        p -> generated = true;
        return p;
    }

    inline AstModifierKeyword* GenModifierKeyword(TokenIndex token)
    {
        AstModifierKeyword* p = NewModifierKeyword(token);
        p -> generated = true;
        return p;
    }

    inline AstModifiers* GenModifiers()
    {
        AstModifiers* p = NewModifiers();
        p -> generated = true;
        return p;
    }

    inline AstPackageDeclaration* GenPackageDeclaration()
    {
        AstPackageDeclaration* p = NewPackageDeclaration();
        p -> generated = true;
        return p;
    }

    inline AstImportDeclaration* GenImportDeclaration()
    {
        AstImportDeclaration* p = NewImportDeclaration();
        p -> generated = true;
        return p;
    }

    inline AstCompilationUnit* GenCompilationUnit()
    {
        AstCompilationUnit* p = NewCompilationUnit();
        p -> generated = true;
        return p;
    }

    inline AstEmptyDeclaration* GenEmptyDeclaration(TokenIndex t)
    {
        AstEmptyDeclaration* p = NewEmptyDeclaration(t);
        p -> generated = true;
        return p;
    }

    inline AstClassBody* GenClassBody()
    {
        AstClassBody* p = NewClassBody();
        p -> generated = true;
        return p;
    }

    inline AstTypeParameter* GenTypeParameter(TokenIndex token)
    {
        AstTypeParameter* p = NewTypeParameter(token);
        p -> generated = true;
        return p;
    }

    inline AstTypeParameters* GenTypeParameters()
    {
        AstTypeParameters* p = NewTypeParameters();
        p -> generated = true;
        return p;
    }

    inline AstClassDeclaration* GenClassDeclaration()
    {
        AstClassDeclaration* p = NewClassDeclaration();
        p -> generated = true;
        return p;
    }

    inline AstArrayInitializer* GenArrayInitializer()
    {
        AstArrayInitializer* p = NewArrayInitializer();
        p -> generated = true;
        return p;
    }

    inline AstVariableDeclaratorId* GenVariableDeclaratorId()
    {
        AstVariableDeclaratorId* p = NewVariableDeclaratorId();
        p -> generated = true;
        return p;
    }

    inline AstVariableDeclarator* GenVariableDeclarator()
    {
        AstVariableDeclarator* p = NewVariableDeclarator();
        p -> generated = true;
        return p;
    }

    inline AstFieldDeclaration* GenFieldDeclaration()
    {
        AstFieldDeclaration* p = NewFieldDeclaration();
        p -> generated = true;
        return p;
    }

    inline AstFormalParameter* GenFormalParameter()
    {
        AstFormalParameter* p = NewFormalParameter();
        p -> generated = true;
        return p;
    }

    inline AstMethodDeclarator* GenMethodDeclarator()
    {
        AstMethodDeclarator* p = NewMethodDeclarator();
        p -> generated = true;
        return p;
    }

    inline AstMethodBody* GenMethodBody()
    {
        AstMethodBody* p = NewMethodBody();
        p -> generated = true;
        return p;
    }

    inline AstMethodDeclaration* GenMethodDeclaration()
    {
        AstMethodDeclaration* p = NewMethodDeclaration();
        p -> generated = true;
        return p;
    }

    inline AstInitializerDeclaration* GenInitializerDeclaration()
    {
        AstInitializerDeclaration* p = NewInitializerDeclaration();
        p -> generated = true;
        return p;
    }

    inline AstArguments* GenArguments(TokenIndex left, TokenIndex right)
    {
        AstArguments* p = NewArguments(left, right);
        p -> generated = true;
        return p;
    }

    inline AstThisCall* GenThisCall()
    {
        AstThisCall* p = NewThisCall();
        p -> generated = true;
        return p;
    }

    inline AstSuperCall* GenSuperCall()
    {
        AstSuperCall* p = NewSuperCall();
        p -> generated = true;
        return p;
    }

    inline AstConstructorDeclaration* GenConstructorDeclaration()
    {
        AstConstructorDeclaration* p = NewConstructorDeclaration();
        p -> generated = true;
        return p;
    }

    inline AstEnumDeclaration* GenEnumDeclaration()
    {
        AstEnumDeclaration* p = NewEnumDeclaration();
        p -> generated = true;
        return p;
    }

    inline AstEnumConstant* GenEnumConstant(TokenIndex t)
    {
        AstEnumConstant* p = NewEnumConstant(t);
        p -> generated = true;
        return p;
    }

    inline AstInterfaceDeclaration* GenInterfaceDeclaration()
    {
        AstInterfaceDeclaration* p = NewInterfaceDeclaration();
        p -> generated = true;
        return p;
    }

    inline AstAnnotationDeclaration* GenAnnotationDeclaration(TokenIndex t)
    {
        AstAnnotationDeclaration* p = NewAnnotationDeclaration(t);
        p -> generated = true;
        return p;
    }

    inline AstLocalVariableStatement* GenLocalVariableStatement()
    {
        AstLocalVariableStatement* p = NewLocalVariableStatement();
        p -> generated = true;
        return p;
    }

    inline AstLocalClassStatement* GenLocalClassStatement(AstClassDeclaration* decl)
    {
        AstLocalClassStatement* p = NewLocalClassStatement(decl);
        p -> generated = true;
        return p;
    }

    inline AstLocalClassStatement* GenLocalClassStatement(AstEnumDeclaration* decl)
    {
        AstLocalClassStatement* p = NewLocalClassStatement(decl);
        p -> generated = true;
        return p;
    }

    inline AstIfStatement* GenIfStatement()
    {
        AstIfStatement* p = NewIfStatement();
        p -> generated = true;
        return p;
    }

    inline AstEmptyStatement* GenEmptyStatement(TokenIndex token)
    {
        AstEmptyStatement* p = NewEmptyStatement(token);
        p -> generated = true;
        return p;
    }

    inline AstExpressionStatement* GenExpressionStatement()
    {
        AstExpressionStatement* p = NewExpressionStatement();
        p -> generated = true;
        return p;
    }

    inline AstSwitchLabel* GenSwitchLabel()
    {
        AstSwitchLabel* p = NewSwitchLabel();
        p -> generated = true;
        return p;
    }

    inline AstSwitchBlockStatement* GenSwitchBlockStatement()
    {
        AstSwitchBlockStatement* p = NewSwitchBlockStatement();
        p -> generated = true;
        return p;
    }

    inline AstSwitchStatement* GenSwitchStatement()
    {
        AstSwitchStatement* p = NewSwitchStatement();
        p -> generated = true;
        return p;
    }

    inline AstWhileStatement* GenWhileStatement()
    {
        AstWhileStatement* p = NewWhileStatement();
        p -> generated = true;
        return p;
    }

    inline AstDoStatement* GenDoStatement()
    {
        AstDoStatement* p = NewDoStatement();
        p -> generated = true;
        return p;
    }

    inline AstForStatement* GenForStatement()
    {
        AstForStatement* p = NewForStatement();
        p -> generated = true;
        return p;
    }

    inline AstForeachStatement* GenForeachStatement()
    {
        AstForeachStatement* p = NewForeachStatement();
        p -> generated = true;
        return p;
    }

    inline AstBreakStatement* GenBreakStatement()
    {
        AstBreakStatement* p = NewBreakStatement();
        p -> generated = true;
        return p;
    }

    inline AstContinueStatement* GenContinueStatement()
    {
        AstContinueStatement* p = NewContinueStatement();
        p -> generated = true;
        return p;
    }

    inline AstReturnStatement* GenReturnStatement()
    {
        AstReturnStatement* p = NewReturnStatement();
        p -> generated = true;
        return p;
    }

    inline AstThrowStatement* GenThrowStatement()
    {
        AstThrowStatement* p = NewThrowStatement();
        p -> generated = true;
        return p;
    }

    inline AstSynchronizedStatement* GenSynchronizedStatement()
    {
        AstSynchronizedStatement* p = NewSynchronizedStatement();
        p -> generated = true;
        return p;
    }

    inline AstAssertStatement* GenAssertStatement()
    {
        AstAssertStatement* p = NewAssertStatement();
        p -> generated = true;
        return p;
    }

    inline AstCatchClause* GenCatchClause()
    {
        AstCatchClause* p = NewCatchClause();
        p -> generated = true;
        return p;
    }

    inline AstFinallyClause* GenFinallyClause()
    {
        AstFinallyClause* p = NewFinallyClause();
        p -> generated = true;
        return p;
    }

    inline AstTryStatement* GenTryStatement()
    {
        AstTryStatement* p = NewTryStatement();
        p -> generated = true;
        return p;
    }

    inline AstIntegerLiteral* GenIntegerLiteral(TokenIndex token)
    {
        AstIntegerLiteral* p = NewIntegerLiteral(token);
        p -> generated = true;
        return p;
    }

    inline AstLongLiteral* GenLongLiteral(TokenIndex token)
    {
        AstLongLiteral* p = NewLongLiteral(token);
        p -> generated = true;
        return p;
    }

    inline AstFloatLiteral* GenFloatLiteral(TokenIndex token)
    {
        AstFloatLiteral* p = NewFloatLiteral(token);
        p -> generated = true;
        return p;
    }

    inline AstDoubleLiteral* GenDoubleLiteral(TokenIndex token)
    {
        AstDoubleLiteral* p = NewDoubleLiteral(token);
        p -> generated = true;
        return p;
    }

    inline AstTrueLiteral* GenTrueLiteral(TokenIndex token)
    {
        AstTrueLiteral* p = NewTrueLiteral(token);
        p -> generated = true;
        return p;
    }

    inline AstFalseLiteral* GenFalseLiteral(TokenIndex token)
    {
        AstFalseLiteral* p = NewFalseLiteral(token);
        p -> generated = true;
        return p;
    }

    inline AstStringLiteral* GenStringLiteral(TokenIndex token)
    {
        AstStringLiteral* p = NewStringLiteral(token);
        p -> generated = true;
        return p;
    }

    inline AstCharacterLiteral* GenCharacterLiteral(TokenIndex token)
    {
        AstCharacterLiteral* p = NewCharacterLiteral(token);
        p -> generated = true;
        return p;
    }

    inline AstNullLiteral* GenNullLiteral(TokenIndex token)
    {
        AstNullLiteral* p = NewNullLiteral(token);
        p -> generated = true;
        return p;
    }

    inline AstClassLiteral* GenClassLiteral(TokenIndex token)
    {
        AstClassLiteral* p = NewClassLiteral(token);
        p -> generated = true;
        return p;
    }

    inline AstThisExpression* GenThisExpression(TokenIndex token)
    {
        AstThisExpression* p = NewThisExpression(token);
        p -> generated = true;
        return p;
    }

    inline AstSuperExpression* GenSuperExpression(TokenIndex token)
    {
        AstSuperExpression* p = NewSuperExpression(token);
        p -> generated = true;
        return p;
    }

    inline AstParenthesizedExpression* GenParenthesizedExpression()
    {
        AstParenthesizedExpression* p = NewParenthesizedExpression();
        p -> generated = true;
        return p;
    }

    inline AstClassCreationExpression* GenClassCreationExpression()
    {
        AstClassCreationExpression* p = NewClassCreationExpression();
        p -> generated = true;
        return p;
    }

    inline AstDimExpr* GenDimExpr()
    {
        AstDimExpr* p = NewDimExpr();
        p -> generated = true;
        return p;
    }

    inline AstArrayCreationExpression* GenArrayCreationExpression()
    {
        AstArrayCreationExpression* p = NewArrayCreationExpression();
        p -> generated = true;
        return p;
    }

    inline AstFieldAccess* GenFieldAccess()
    {
        AstFieldAccess* p = NewFieldAccess();
        p -> generated = true;
        return p;
    }

    inline AstMethodInvocation* GenMethodInvocation(TokenIndex t)
    {
        AstMethodInvocation* p = NewMethodInvocation(t);
        p -> generated = true;
        return p;
    }

    inline AstArrayAccess* GenArrayAccess()
    {
        AstArrayAccess* p = NewArrayAccess();
        p -> generated = true;
        return p;
    }

    inline AstPostUnaryExpression* GenPostUnaryExpression(AstPostUnaryExpression::PostUnaryExpressionTag tag)
    {
        AstPostUnaryExpression* p = NewPostUnaryExpression(tag);
        p -> generated = true;
        return p;
    }

    inline AstPreUnaryExpression* GenPreUnaryExpression(AstPreUnaryExpression::PreUnaryExpressionTag tag)
    {
        AstPreUnaryExpression* p = NewPreUnaryExpression(tag);
        p -> generated = true;
        return p;
    }

    inline AstCastExpression* GenCastExpression()
    {
        AstCastExpression* p = NewCastExpression();
        p -> generated = true;
        return p;
    }

    inline AstBinaryExpression* GenBinaryExpression(AstBinaryExpression::BinaryExpressionTag tag)
    {
        AstBinaryExpression* p = NewBinaryExpression(tag);
        p -> generated = true;
        return p;
    }

    inline AstInstanceofExpression* GenInstanceofExpression()
    {
        AstInstanceofExpression* p = NewInstanceofExpression();
        p -> generated = true;
        return p;
    }

    inline AstConditionalExpression* GenConditionalExpression()
    {
        AstConditionalExpression* p = NewConditionalExpression();
        p -> generated = true;
        return p;
    }

    inline AstAssignmentExpression* GenAssignmentExpression(AstAssignmentExpression::AssignmentExpressionTag tag,
                                                            TokenIndex token)
    {
        AstAssignmentExpression* p = NewAssignmentExpression(tag, token);
        p -> generated = true;
        return p;
    }
};


#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif // STORAGE_POOL_H
