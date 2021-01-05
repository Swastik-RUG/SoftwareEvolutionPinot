#include "../../ast.h"

#ifndef AstForeachStatement_INCLUDED
#define AstForeachStatement_INCLUDED

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

//
// ForeachStatement is added in JDK 1.5 by JSR 201.  It has the syntax
// "for (FormalParameter : expression) statement", where expression must
// be an array type or an instance of java.lang.Iterable. The parser already
// wrapped the statement in a block.
//
class AstForeachStatement : public AstStatement
{
public:
    TokenIndex for_token;
    wchar_t* for_token_string;
    AstFormalParameter* formal_parameter;
    AstExpression* expression;
    AstBlock* statement;

    inline AstForeachStatement()
        : AstStatement(FOREACH)
    {}
    ~AstForeachStatement() { /*delete for_token_string;*/ }

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
};


inline AstForeachStatement* Ast::ForeachStatementCast()
{
    return DYNAMIC_CAST<AstForeachStatement*> (kind == FOREACH ? this : NULL);
}



#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif
