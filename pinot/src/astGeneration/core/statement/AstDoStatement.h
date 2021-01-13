#include "../../ast.h"

#ifndef AstDoStatement_INCLUDED
#define AstDoStatement_INCLUDED

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

    //
    // DoStatement --> <DO, Label_opt, do_token, Expression, Statement, ;_token>
    //
    class AstDoStatement : public AstStatement
    {
    public:
        TokenIndex do_token;
        wchar_t *do_token_string;
        AstBlock *statement;
        TokenIndex while_token;
        wchar_t *while_token_string;
        AstExpression *expression;
        TokenIndex semicolon_token;

        inline AstDoStatement()
            : AstStatement(DO)
        {
        }
        ~AstDoStatement()
        {
            //delete do_token_string;
            //delete while_token_string;
        }

#ifdef JIKES_DEBUG
        virtual void Print(LexStream &);
        virtual void Print();
        virtual void Unparse(Ostream &, LexStream *);
#endif // JIKES_DEBUG

        virtual Ast *Clone(StoragePool *);
        virtual Ast *Clone(StoragePool *, LexStream &);
        virtual void Lexify(LexStream &);

        virtual TokenIndex LeftToken() { return do_token; }
        virtual TokenIndex RightToken() { return semicolon_token; }
    };

    inline AstDoStatement *Ast::DoStatementCast()
    {
        return DYNAMIC_CAST<AstDoStatement *>(kind == DO ? this : NULL);
    }

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif
