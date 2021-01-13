#include "AstForeachStatement.h"
#include "../../storage/storagepool.h"
#include "../../../declarations/stream.h"

#ifdef JIKES_DEBUG
#endif // JIKES_DEBUG

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

Ast* AstForeachStatement::Clone(StoragePool* ast_pool)
{
    AstForeachStatement* clone = ast_pool -> GenForeachStatement();
    clone -> for_token = for_token;

    clone -> for_token_string = for_token_string;

    clone -> formal_parameter =
        (AstFormalParameter*) formal_parameter -> Clone(ast_pool);
    clone -> expression = (AstExpression*) expression -> Clone(ast_pool);
    clone -> statement = (AstBlock*) statement -> Clone(ast_pool);
    return clone;
}

Ast* AstForeachStatement::Clone(StoragePool* ast_pool, LexStream& lex_stream)
{
    AstForeachStatement* clone = ast_pool -> GenForeachStatement();
    clone -> for_token = for_token;
    clone -> formal_parameter =
        (AstFormalParameter*) formal_parameter -> Clone(ast_pool, lex_stream);
    clone -> expression = (AstExpression*) expression -> Clone(ast_pool, lex_stream);
    clone -> statement = (AstBlock*) statement -> Clone(ast_pool, lex_stream);


    clone -> for_token_string = new wchar_t[wcslen(lex_stream.NameString(for_token)) + 1];
    wcscpy(clone -> for_token_string, lex_stream.NameString(for_token));


    clone -> for_token_string = const_cast<wchar_t*>(lex_stream.NameString(for_token));

    return clone;
}

void AstForeachStatement::Lexify(LexStream& lex_stream)
{
	formal_parameter -> Lexify(lex_stream);
	expression -> Lexify(lex_stream);
	statement -> Lexify(lex_stream);

	for_token_string = const_cast<wchar_t*>(lex_stream.NameString(for_token));
}

void AstForeachStatement::Print()
{
    Coutput << '#' << id << " (ForeachStatement):  ("
            << for_token_string << "( #"
            << formal_parameter -> id << ": #" << expression -> id
            << ") #" << statement -> id << endl;
    formal_parameter -> Print();
    expression -> Print();
    statement -> Print();
}

void AstForeachStatement::Print(LexStream& lex_stream)
{
    Coutput << '#' << id << " (ForeachStatement):  ("
            << lex_stream.NameString(for_token) << "( #"
            << formal_parameter -> id << ": #" << expression -> id
            << ") #" << statement -> id << endl;
    formal_parameter -> Print(lex_stream);
    expression -> Print(lex_stream);
    statement -> Print(lex_stream);
}



#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif
