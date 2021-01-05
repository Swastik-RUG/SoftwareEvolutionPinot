#include "../../ast.h"

#ifndef AstForStatement_INCLUDED
#define AstForStatement_INCLUDED

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

//
// Represents the traditional for statement. The parser has already enclosed
// the overall for statement in its own block, as well as the enclosed
// statement.
//
class AstForStatement : public AstStatement
{
    StoragePool* pool;
    AstArray<AstStatement*>* for_init_statements;
    AstArray<AstExpressionStatement*>* for_update_statements;

public:
    TokenIndex for_token;
    wchar_t* for_token_string;

    AstExpression* end_expression_opt;
    AstBlock* statement;

    inline AstForStatement(StoragePool* p)
        : AstStatement(FOR)
        , pool(p)
    {}
    ~AstForStatement() { /*delete for_token_string;*/ }

    inline AstStatement*& ForInitStatement(unsigned i)
    {
        return (*for_init_statements)[i];
    }
    inline unsigned NumForInitStatements()
    {
        return for_init_statements ? for_init_statements -> Length() : 0;
    }
    inline void AllocateForInitStatements(unsigned estimate = 1);
    inline void AddForInitStatement(AstStatement*);

    inline AstExpressionStatement*& ForUpdateStatement(unsigned i)
    {
        return (*for_update_statements)[i];
    }
    inline unsigned NumForUpdateStatements()
    {
        return for_update_statements ? for_update_statements -> Length() : 0;
    }
    inline void AllocateForUpdateStatements(unsigned estimate = 1);
    inline void AddForUpdateStatement(AstExpressionStatement*);

#ifdef JIKES_DEBUG
    virtual void Print(LexStream&);
    virtual void Print();
    virtual void Unparse(Ostream&, LexStream*);
#endif // JIKES_DEBUG

    virtual Ast* Clone(StoragePool*);
    virtual Ast* Clone(StoragePool*, LexStream&);
    virtual void Lexify(LexStream&);

    virtual TokenIndex LeftToken() { return for_token; }
    virtual TokenIndex RightToken() { return statement -> right_brace_token; }
    virtual void PrintAssociation(AssocTable* , wchar_t*, wchar_t*, wchar_t*, LexStream&);
};


inline AstForStatement* Ast::ForStatementCast()
{
    return DYNAMIC_CAST<AstForStatement*> (kind == FOR ? this : NULL);
}


inline void AstForStatement::AllocateForInitStatements(unsigned estimate)
{
    assert(! for_init_statements);
    for_init_statements = new (pool) AstArray<AstStatement*> (pool, estimate);
}

inline void AstForStatement::AddForInitStatement(AstStatement* statement)
{
    assert(for_init_statements);
    for_init_statements -> Next() = statement;
}

inline void AstForStatement::AllocateForUpdateStatements(unsigned estimate)
{
    assert(! for_update_statements);
    for_update_statements =
        new (pool) AstArray<AstExpressionStatement*> (pool, estimate);
}

inline void AstForStatement::AddForUpdateStatement(AstExpressionStatement* statement)
{
    assert(for_update_statements);
    for_update_statements -> Next() = statement;
}

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif
