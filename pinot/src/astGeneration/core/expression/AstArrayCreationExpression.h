#include "../../ast.h"

#ifndef AstArrayCreationExpression_INCLUDED
#define AstArrayCreationExpression_INCLUDED

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

//
// ArrayCreationExpression --> <ARRAY_CREATION, new_token, Type, DimExprs,
// Brackets>
//
class AstArrayCreationExpression : public AstExpression
{
    StoragePool* pool;
    AstArray<AstDimExpr*>* dim_exprs;

public:
    TokenIndex new_token;
    wchar_t* new_token_string;
    AstType* array_type;
    AstBrackets* brackets_opt;
    AstArrayInitializer* array_initializer_opt;

    inline AstArrayCreationExpression(StoragePool* p)
        : AstExpression(ARRAY_CREATION)
        , pool(p)
    {}
    ~AstArrayCreationExpression() { /*delete new_token_string;*/ }

    inline AstDimExpr*& DimExpr(unsigned i) { return (*dim_exprs)[i]; }
    inline unsigned NumDimExprs()
    {
        return dim_exprs ? dim_exprs -> Length() : 0;
    }
    inline void AllocateDimExprs(unsigned estimate = 1);
    inline void AddDimExpr(AstDimExpr*);

    inline unsigned NumBrackets()
    {
        return brackets_opt ? brackets_opt -> dims : 0;
    }

#ifdef JIKES_DEBUG
    virtual void Print(LexStream&);
    virtual void Print();
    virtual void Unparse(Ostream&, LexStream*);
#endif // JIKES_DEBUG

    virtual Ast* Clone(StoragePool*);
    virtual Ast* Clone(StoragePool*, LexStream&);
    virtual void Lexify(LexStream&);

    virtual TokenIndex LeftToken() { return new_token; }
    virtual TokenIndex RightToken()
    {
        return array_initializer_opt
            ? array_initializer_opt -> right_brace_token
            : brackets_opt ? brackets_opt -> right_bracket_token
            : DimExpr(NumDimExprs() - 1) -> right_bracket_token;
    }
};

inline AstArrayCreationExpression* Ast::ArrayCreationExpressionCast()
{
    return DYNAMIC_CAST<AstArrayCreationExpression*>
        (kind == ARRAY_CREATION ? this : NULL);
}

inline void AstArrayCreationExpression::AllocateDimExprs(unsigned estimate)
{
    assert(! dim_exprs);
    dim_exprs = new (pool) AstArray<AstDimExpr*> (pool, estimate);
}

inline void AstArrayCreationExpression::AddDimExpr(AstDimExpr* dim_expr)
{
    assert(dim_exprs);
    dim_exprs -> Next() = dim_expr;
}


#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif
