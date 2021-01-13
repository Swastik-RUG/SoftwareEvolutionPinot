#include "AstDoStatement.h"
#include "../../storage/storagepool.h"
#include "../../../declarations/stream.h"

#ifdef JIKES_DEBUG
#endif // JIKES_DEBUG

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

void AstDoStatement::Print()
{
    Coutput << '#' << id << " (DoStatement):  "
            << do_token_string
            << " { #" << statement -> id << " } "
            << while_token_string
            << " ( #" << expression -> id << " ) #" << endl;

    statement -> Print();
    expression -> Print();
}

void AstDoStatement::Print(LexStream& lex_stream)
{
    Coutput << '#' << id << " (DoStatement):  "
            << lex_stream.NameString(do_token)
            << " { #" << statement -> id << " } "
            << lex_stream.NameString(while_token)
            << " ( #" << expression -> id << " ) #" << endl;

    statement -> Print(lex_stream);
    expression -> Print(lex_stream);
}

Ast* AstDoStatement::Clone(StoragePool* ast_pool)
{
    AstDoStatement* clone = ast_pool -> GenDoStatement();
    clone -> do_token = do_token;

    clone -> do_token_string = do_token_string;

    clone -> statement = (AstBlock*) statement -> Clone(ast_pool);
    clone -> while_token = while_token;

    clone -> while_token_string = while_token_string;

    clone -> expression = (AstExpression*) expression -> Clone(ast_pool);
    clone -> semicolon_token = semicolon_token;
    return clone;
}

Ast* AstDoStatement::Clone(StoragePool* ast_pool, LexStream& lex_stream)
{
    AstDoStatement* clone = ast_pool -> GenDoStatement();
    clone -> do_token = do_token;
    clone -> statement = (AstBlock*) statement -> Clone(ast_pool, lex_stream);
    clone -> while_token = while_token;
    clone -> expression = (AstExpression*) expression -> Clone(ast_pool, lex_stream);
    clone -> semicolon_token = semicolon_token;


    clone -> do_token_string = new wchar_t[wcslen(lex_stream.NameString(do_token)) + 1];
    clone -> while_token_string = new wchar_t[wcslen(lex_stream.NameString(while_token)) + 1];
    wcscpy(clone -> do_token_string, lex_stream.NameString(do_token));
    wcscpy(clone -> while_token_string, lex_stream.NameString(while_token));


    clone -> do_token_string = const_cast<wchar_t*>(lex_stream.NameString(do_token));
    clone -> while_token_string = const_cast<wchar_t*>(lex_stream.NameString(while_token));

    return clone;
}

void AstDoStatement::Lexify(LexStream& lex_stream)
{
	statement -> Lexify(lex_stream);
	expression -> Lexify(lex_stream);

	do_token_string = const_cast<wchar_t*>(lex_stream.NameString(do_token));
	while_token_string = const_cast<wchar_t*>(lex_stream.NameString(while_token));
}

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif
