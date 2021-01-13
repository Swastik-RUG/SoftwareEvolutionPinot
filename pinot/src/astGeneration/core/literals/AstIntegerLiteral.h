#include "../../ast.h"

#ifndef AstIntegerLiteral_INCLUDED
#define AstIntegerLiteral_INCLUDED

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

    //
    // Represents an int literal.
    //
    class AstIntegerLiteral : public AstExpression
    {
    public:
        TokenIndex integer_literal_token;
        wchar_t *integer_literal_token_string;

        inline AstIntegerLiteral(TokenIndex token)
            : AstExpression(INTEGER_LITERAL), integer_literal_token(token)
        {
        }
        ~AstIntegerLiteral()
        { /*delete integer_literal_token_string;*/
        }

#ifdef JIKES_DEBUG
        virtual void Print(LexStream &);
        virtual void Print();
        virtual void Unparse(Ostream &, LexStream *);
#endif // JIKES_DEBUG

        virtual Ast *Clone(StoragePool *);
        virtual Ast *Clone(StoragePool *, LexStream &);
        virtual void Lexify(LexStream &);

        virtual TokenIndex LeftToken() { return integer_literal_token; }
        virtual TokenIndex RightToken() { return integer_literal_token; }
    };

inline AstIntegerLiteral* Ast::IntegerLiteralCast()
{
    return DYNAMIC_CAST<AstIntegerLiteral*>
        (kind == INTEGER_LITERAL ? this : NULL);
}

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif
