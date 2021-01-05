
#include "AstWhileStatement.h"
#include "../../storage/storagepool.h"
#include "../../../declarations/stream.h"

#ifdef JIKES_DEBUG
#endif // JIKES_DEBUG

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

void AstWhileStatement::Print(LexStream& lex_stream)
{
    Coutput << '#' << id << " (WhileStatement):  "
            << lex_stream.NameString(while_token)
            << " ( #" << expression -> id << " ) #" << statement -> id << endl;
    expression -> Print(lex_stream);
    statement -> Print(lex_stream);
}

Ast* AstWhileStatement::Clone(StoragePool* ast_pool)
{
    AstWhileStatement* clone = ast_pool -> GenWhileStatement();
    clone -> while_token = while_token;

    clone -> while_token_string = while_token_string;

    clone -> expression = (AstExpression*) expression -> Clone(ast_pool);
    clone -> statement = (AstBlock*) statement -> Clone(ast_pool);
    return clone;
}

void AstWhileStatement::PrintAssociation(AssocTable* assoc_table, wchar_t* package_name, wchar_t* class_name, wchar_t* method_name, LexStream& lex_stream)
{
	statement -> PrintAssociation(assoc_table, package_name, class_name, method_name, lex_stream);
}

Ast* AstWhileStatement::Clone(StoragePool* ast_pool, LexStream& lex_stream)
{
    AstWhileStatement* clone = ast_pool -> GenWhileStatement();
    clone -> while_token = while_token;
    clone -> expression = (AstExpression*) expression -> Clone(ast_pool, lex_stream);
    clone -> statement = (AstBlock*) statement -> Clone(ast_pool, lex_stream);


    clone -> while_token_string = new wchar_t[wcslen(lex_stream.NameString(while_token)) +1];
    wcscpy(clone -> while_token_string, lex_stream.NameString(while_token));


    clone -> while_token_string = const_cast<wchar_t*>(lex_stream.NameString(while_token));

    return clone;
}

void AstWhileStatement::Lexify(LexStream& lex_stream)
{
	expression -> Lexify(lex_stream);
	statement -> Lexify(lex_stream);

	while_token_string = const_cast<wchar_t*>(lex_stream.NameString(while_token));
}

void AstWhileStatement::Print()
{
    Coutput << '#' << id << " (WhileStatement):  "
            << while_token_string
            << " ( #" << expression -> id << " ) #" << statement -> id << endl;
    expression -> Print();
    statement -> Print();
}

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif
