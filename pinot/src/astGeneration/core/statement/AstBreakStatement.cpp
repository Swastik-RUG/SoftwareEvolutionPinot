#include "AstBreakStatement.h"
#include "../../storage/storagepool.h"
#include "../../../declarations/stream.h"

#ifdef JIKES_DEBUG
#endif // JIKES_DEBUG

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

Ast* AstBreakStatement::Clone(StoragePool* ast_pool)
{
    AstBreakStatement* clone = ast_pool -> GenBreakStatement();
    clone -> break_token = break_token;
    clone -> identifier_token_opt = identifier_token_opt;

    clone -> break_token_string = break_token_string;
    clone -> identifier_token_opt_string = identifier_token_opt_string;

    clone -> semicolon_token = semicolon_token;
    clone -> nesting_level = nesting_level;
    return clone;
}

Ast* AstBreakStatement::Clone(StoragePool* ast_pool, LexStream& lex_stream)
{
    AstBreakStatement* clone = ast_pool -> GenBreakStatement();
    clone -> break_token = break_token;
    clone -> identifier_token_opt = identifier_token_opt;
    clone -> semicolon_token = semicolon_token;
    clone -> nesting_level = nesting_level;

    clone -> break_token_string = new wchar_t[wcslen(lex_stream.NameString(break_token)) + 1];
    clone -> identifier_token_opt_string = new wchar_t[wcslen(lex_stream.NameString(identifier_token_opt)) + 1];
    wcscpy(clone -> break_token_string, lex_stream.NameString(break_token));
    wcscpy(clone -> identifier_token_opt_string, lex_stream.NameString(identifier_token_opt));

    clone -> break_token_string = const_cast<wchar_t*>(lex_stream.NameString(break_token));
    clone -> identifier_token_opt_string = const_cast<wchar_t*>(lex_stream.NameString(identifier_token_opt));

    return clone;
}


void AstBreakStatement::Lexify(LexStream& lex_stream)
{
	break_token_string = const_cast<wchar_t*>(lex_stream.NameString(break_token));
    	identifier_token_opt_string = const_cast<wchar_t*>(lex_stream.NameString(identifier_token_opt));
}

void AstBreakStatement::Print()
{
    Coutput << '#' << id << " (BreakStatement):  "
            << break_token_string << ' '
            << (identifier_token_opt
                ? identifier_token_opt_string : L"")
            << " at nesting_level " << nesting_level << endl;
}

void AstBreakStatement::Print(LexStream& lex_stream)
{
    Coutput << '#' << id << " (BreakStatement):  "
            << lex_stream.NameString(break_token) << ' '
            << (identifier_token_opt
                ? lex_stream.NameString(identifier_token_opt) : L"")
            << " at nesting_level " << nesting_level << endl;
}

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

