#include "../../ast.h"

#ifndef AstLongLiteral_INCLUDED
#define AstLongLiteral_INCLUDED

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

//
// LongLiteral --> <LONG_LITERAL, long_literal_token, value>
//
class AstLongLiteral : public AstExpression
{
public:
    TokenIndex long_literal_token;
    wchar_t* long_literal_token_string;

    inline AstLongLiteral(TokenIndex token)
        : AstExpression(LONG_LITERAL)
        , long_literal_token(token)
    {}
    ~AstLongLiteral() { /*delete long_literal_token_string;*/ }

#ifdef JIKES_DEBUG
    virtual void Print(LexStream&);
    virtual void Print();
    virtual void Unparse(Ostream&, LexStream*);
#endif // JIKES_DEBUG

    virtual Ast* Clone(StoragePool*);
    virtual Ast* Clone(StoragePool*, LexStream&);
    virtual void Lexify(LexStream&);

    virtual TokenIndex LeftToken() { return long_literal_token; }
    virtual TokenIndex RightToken() { return long_literal_token; }
};

inline AstLongLiteral* Ast::LongLiteralCast()
{
    return DYNAMIC_CAST<AstLongLiteral*> (kind == LONG_LITERAL ? this : NULL);
}

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif
