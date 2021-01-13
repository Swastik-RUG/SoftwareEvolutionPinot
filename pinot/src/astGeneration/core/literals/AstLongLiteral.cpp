#include "AstLongLiteral.h"
#include "../../storage/storagepool.h"
#include "../../../declarations/stream.h"

#ifdef JIKES_DEBUG
#endif // JIKES_DEBUG

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

Ast* AstLongLiteral::Clone(StoragePool* ast_pool)
{
    AstLongLiteral *clone = ast_pool -> GenLongLiteral(long_literal_token);

    clone->long_literal_token_string = long_literal_token_string;
    clone->symbol = symbol;

    return clone;
}

Ast* AstLongLiteral::Clone(StoragePool* ast_pool, LexStream& lex_stream)
{
    AstLongLiteral* clone = ast_pool -> GenLongLiteral(long_literal_token);


    clone -> long_literal_token_string = new wchar_t[wcslen(lex_stream.NameString(long_literal_token)) + 1];
    wcscpy(clone -> long_literal_token_string, lex_stream.NameString(long_literal_token));

    clone -> long_literal_token_string = const_cast<wchar_t*>(lex_stream.NameString(long_literal_token));

    return clone;
}

void AstLongLiteral::Lexify(LexStream& lex_stream)
{
	long_literal_token_string = const_cast<wchar_t*>(lex_stream.NameString(long_literal_token));
}

void AstLongLiteral::Print()
{
    Coutput << '#' << id << " (LongLiteral):  "
            << long_literal_token_string
            << endl;
}


void AstLongLiteral::Print(LexStream& lex_stream)
{
    Coutput << '#' << id << " (LongLiteral):  "
            << lex_stream.NameString(long_literal_token)
            << endl;
}

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

