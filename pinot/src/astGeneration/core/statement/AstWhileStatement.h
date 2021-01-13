#include "../../ast.h"

#ifndef AstWhileStatement_INCLUDED
#define AstWhileStatement_INCLUDED

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

//
// WhileStatement --> <WHILE, Label_opt, while_token, Expression, Statement>
//
class AstWhileStatement : public AstStatement
{
public:
    TokenIndex while_token;
    wchar_t* while_token_string;
    AstExpression* expression;
    AstBlock* statement;

    inline AstWhileStatement()
        : AstStatement(WHILE)
    {}
    ~AstWhileStatement() { /*delete while_token_string;*/ }

#ifdef JIKES_DEBUG
    virtual void Print(LexStream&);
    virtual void Print();
    virtual void Unparse(Ostream&, LexStream*);
#endif // JIKES_DEBUG

    virtual Ast* Clone(StoragePool*);
    virtual Ast* Clone(StoragePool*, LexStream&);
    virtual void Lexify(LexStream&);

    virtual TokenIndex LeftToken() { return while_token; }
    virtual TokenIndex RightToken() { return statement -> right_brace_token; }
    virtual void PrintAssociation(AssocTable* , wchar_t*, wchar_t*, wchar_t*, LexStream&);
};

inline AstWhileStatement* Ast::WhileStatementCast()
{
    return DYNAMIC_CAST<AstWhileStatement*> (kind == WHILE ? this : NULL);
}

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif