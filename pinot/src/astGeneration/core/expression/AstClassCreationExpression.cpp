#include "AstClassCreationExpression.h"
#include "../../storage/storagepool.h"
#include "../../../declarations/stream.h"

#ifdef JIKES_DEBUG
#endif // JIKES_DEBUG

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

Ast* AstClassCreationExpression::Clone(StoragePool* ast_pool)
{
    AstClassCreationExpression* clone =
        ast_pool -> GenClassCreationExpression();
    if (base_opt)
        clone -> base_opt = (AstExpression*) base_opt -> Clone(ast_pool);
    clone -> new_token = new_token;

    clone -> new_token_string = new_token_string;
    clone->symbol = symbol;

    if (type_arguments_opt)
        clone -> type_arguments_opt =
            (AstTypeArguments*) type_arguments_opt -> Clone(ast_pool);
    clone -> class_type = (AstTypeName*) class_type -> Clone(ast_pool);
    clone -> arguments = (AstArguments*) arguments -> Clone(ast_pool);
    if (class_body_opt)
        clone -> class_body_opt =
            (AstClassBody*) class_body_opt -> Clone(ast_pool);
    if (resolution_opt)
        clone -> resolution_opt =
            (AstClassCreationExpression*) resolution_opt -> Clone(ast_pool);
    return clone;
}

void AstClassCreationExpression::PrintAssociation(AssocTable* assoc_table, wchar_t* package_name, wchar_t* class_name, wchar_t* method_name, LexStream& lex_stream)
{
	wchar_t* type_name = const_cast<wchar_t*>(lex_stream.NameString(class_type -> name -> identifier_token));
	if (!isPrimitiveType(type_name))
		assoc_table -> addAssociation( Assoc::OC, Assoc::PRIVATE, NULL, type_name, package_name, class_name, method_name);
}

Ast* AstClassCreationExpression::Clone(StoragePool* ast_pool, LexStream& lex_stream)
{
    AstClassCreationExpression* clone =
        ast_pool -> GenClassCreationExpression();

    clone -> base_opt = (base_opt)
		? (AstExpression*) base_opt -> Clone(ast_pool, lex_stream)
		: NULL;
    clone -> new_token = new_token;

    clone -> type_arguments_opt = (type_arguments_opt)
		? (AstTypeArguments*) type_arguments_opt -> Clone(ast_pool, lex_stream)
		: NULL;
    clone -> class_type = (AstTypeName*) class_type -> Clone(ast_pool, lex_stream);
    clone -> arguments = (AstArguments*) arguments -> Clone(ast_pool, lex_stream);

    clone -> class_body_opt = (class_body_opt)
		? (AstClassBody*) class_body_opt -> Clone(ast_pool, lex_stream)
		: NULL;

    clone -> resolution_opt = (resolution_opt)
		? (AstClassCreationExpression*) resolution_opt -> Clone(ast_pool, lex_stream)
		: NULL;

    clone -> new_token_string = new wchar_t[wcslen(lex_stream.NameString(new_token)) + 1];
    wcscpy(clone -> new_token_string, lex_stream.NameString(new_token));

    clone -> new_token_string = const_cast<wchar_t*>(lex_stream.NameString(new_token));

    return clone;
}

void AstClassCreationExpression::Lexify(LexStream& lex_stream)
{
	if (base_opt)
		base_opt -> Lexify(lex_stream);

	if (type_arguments_opt)
		type_arguments_opt -> Lexify(lex_stream);

	class_type -> Lexify(lex_stream);
	arguments -> Lexify(lex_stream);

	if (class_body_opt)
		class_body_opt -> Lexify(lex_stream);

	if (resolution_opt)
		resolution_opt -> Lexify(lex_stream);
	new_token_string = const_cast<wchar_t*>(lex_stream.NameString(new_token));
}

void AstClassCreationExpression::Print()
{
    Coutput << '#' << id << " (ClassCreationExpression):  #"
            << (base_opt ? base_opt -> id : 0) << ' '
            << new_token_string << " #"
            << (type_arguments_opt ? type_arguments_opt -> id : 0) << " #"
            << class_type -> id << " #" << arguments -> id << " #"
            << (class_body_opt ? class_body_opt -> id : 0) << endl;
    if (base_opt)
        base_opt -> Print();
    if (type_arguments_opt)
        type_arguments_opt -> Print();
    class_type -> Print();
    arguments -> Print();
    if (class_body_opt)
        class_body_opt -> Print();
}

void AstClassCreationExpression::Print(LexStream& lex_stream)
{
    Coutput << '#' << id << " (ClassCreationExpression):  #"
            << (base_opt ? base_opt -> id : 0) << ' '
            << lex_stream.NameString(new_token) << " #"
            << (type_arguments_opt ? type_arguments_opt -> id : 0) << " #"
            << class_type -> id << " #" << arguments -> id << " #"
            << (class_body_opt ? class_body_opt -> id : 0) << endl;
    if (base_opt)
        base_opt -> Print(lex_stream);
    if (type_arguments_opt)
        type_arguments_opt -> Print(lex_stream);
    class_type -> Print(lex_stream);
    arguments -> Print(lex_stream);
    if (class_body_opt)
        class_body_opt -> Print(lex_stream);
}



#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif