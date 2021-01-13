#include "../../ast.h"

#ifndef AstBreakStatement_INCLUDED
#define AstBreakStatement_INCLUDED

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

//
// BreakStatement --> <BREAK, Label_opt, break_token, identifier_token_opt,
// ;_token>
//
class AstBreakStatement : public AstStatement
{
public:
    TokenIndex break_token;
    wchar_t* break_token_string;
    TokenIndex identifier_token_opt;
    wchar_t* identifier_token_opt_string;
    TokenIndex semicolon_token;
    unsigned nesting_level;

    inline AstBreakStatement()
        : AstStatement(BREAK)
    {}
    ~AstBreakStatement()
	{
		//delete break_token_string;
		//delete identifier_token_opt_string;
	}

#ifdef JIKES_DEBUG
    virtual void Print(LexStream&);
    virtual void Print();
    virtual void Unparse(Ostream&, LexStream*);
#endif // JIKES_DEBUG

    virtual Ast* Clone(StoragePool*);
    virtual Ast* Clone(StoragePool*, LexStream&);
    virtual void Lexify(LexStream&);

    virtual TokenIndex LeftToken() { return break_token; }
    virtual TokenIndex RightToken() { return semicolon_token; }
};

inline AstBreakStatement* Ast::BreakStatementCast()
{
    return DYNAMIC_CAST<AstBreakStatement*> (kind == BREAK ? this : NULL);
}

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif
