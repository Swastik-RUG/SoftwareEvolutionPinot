
#include "AstIntegerLiteral.h"
#include "../../storage/storagepool.h"
#include "../../../declarations/stream.h"

#ifdef JIKES_DEBUG
#endif // JIKES_DEBUG

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

Ast* AstIntegerLiteral::Clone(StoragePool* ast_pool)
{
    AstIntegerLiteral *clone = ast_pool -> GenIntegerLiteral(integer_literal_token);

    clone->integer_literal_token_string = integer_literal_token_string;
    clone->symbol = symbol;

    return clone;
}

Ast* AstIntegerLiteral::Clone(StoragePool* ast_pool, LexStream& lex_stream)
{
    AstIntegerLiteral* clone = ast_pool -> GenIntegerLiteral(integer_literal_token);


    clone -> integer_literal_token_string = new wchar_t[wcslen(lex_stream.NameString(integer_literal_token)) + 1];
    wcscpy(clone -> integer_literal_token_string, lex_stream.NameString(integer_literal_token));

    clone -> integer_literal_token_string = const_cast<wchar_t*>(lex_stream.NameString(integer_literal_token));

    return clone;
}

void AstIntegerLiteral::Lexify(LexStream& lex_stream)
{
	integer_literal_token_string = const_cast<wchar_t*>(lex_stream.NameString(integer_literal_token));
}

void AstIntegerLiteral::Print()
{
    Coutput << '#' << id << " (IntegerLiteral):  "
            << integer_literal_token_string
            << endl;
}

void AstIntegerLiteral::Print(LexStream& lex_stream)
{
    Coutput << '#' << id << " (IntegerLiteral):  "
            << lex_stream.NameString(integer_literal_token)
            << endl;
}



#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif
