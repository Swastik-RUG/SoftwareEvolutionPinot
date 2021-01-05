// #include "AstLiterals.h"
// #include "../storage/storagepool.h"
// #include "../../declarations/stream.h"

// #ifdef JIKES_DEBUG
// #endif // JIKES_DEBUG

// #ifdef HAVE_JIKES_NAMESPACE
// namespace Jikes
// { // Open namespace Jikes block
// #endif

// Ast* AstIntegerLiteral::Clone(StoragePool* ast_pool)
// {
//     AstIntegerLiteral *clone = ast_pool -> GenIntegerLiteral(integer_literal_token);

//     clone->integer_literal_token_string = integer_literal_token_string;
//     clone->symbol = symbol;

//     return clone;
// }

// Ast* AstLongLiteral::Clone(StoragePool* ast_pool)
// {
//     AstLongLiteral *clone = ast_pool -> GenLongLiteral(long_literal_token);

//     clone->long_literal_token_string = long_literal_token_string;
//     clone->symbol = symbol;

//     return clone;
// }

// Ast* AstFloatLiteral::Clone(StoragePool* ast_pool)
// {
//     AstFloatLiteral *clone = ast_pool -> GenFloatLiteral(float_literal_token);

//     clone->float_literal_token_string = float_literal_token_string;
//     clone->symbol = symbol;

//     return clone;
// }

// Ast* AstDoubleLiteral::Clone(StoragePool* ast_pool)
// {
//     AstDoubleLiteral*clone = ast_pool -> GenDoubleLiteral(double_literal_token);

//     clone->double_literal_token_string = double_literal_token_string;
//     clone->symbol = symbol;

//     return clone;
// }

// Ast* AstTrueLiteral::Clone(StoragePool* ast_pool)
// {
//     AstTrueLiteral *clone = ast_pool -> GenTrueLiteral(true_literal_token);

//     clone->true_literal_token_string = true_literal_token_string;
//     clone->symbol = symbol;

//     return clone;
// }

// Ast* AstFalseLiteral::Clone(StoragePool* ast_pool)
// {
//     AstFalseLiteral *clone = ast_pool -> GenFalseLiteral(false_literal_token);

//     clone->false_literal_token_string = false_literal_token_string;
//     clone->symbol = symbol;

//     return clone;
// }

// Ast* AstStringLiteral::Clone(StoragePool* ast_pool)
// {
//     AstStringLiteral *clone = ast_pool -> GenStringLiteral(string_literal_token);

//     clone->string_literal_token_string = string_literal_token_string;
//     clone->symbol = symbol;

//     return clone;
// }

// Ast* AstCharacterLiteral::Clone(StoragePool* ast_pool)
// {
//     AstCharacterLiteral *clone = ast_pool -> GenCharacterLiteral(character_literal_token);

//     clone->character_literal_token_string = character_literal_token_string;
//     clone->symbol = symbol;

//     return clone;
// }

// Ast* AstNullLiteral::Clone(StoragePool* ast_pool)
// {
// 	AstNullLiteral *clone = ast_pool -> GenNullLiteral(null_token);

// 	clone->null_token_string = null_token_string;
//     	clone->symbol = symbol;

// 	return clone;
// }

// Ast* AstClassLiteral::Clone(StoragePool* ast_pool)
// {
//     AstClassLiteral* clone = ast_pool -> GenClassLiteral(class_token);

//     clone->class_token_string = class_token_string;
//     clone->symbol = symbol;

//     clone -> type = (AstTypeName*) type -> Clone(ast_pool);
//     if (resolution_opt)
//         clone -> resolution_opt =
//             (AstExpression*) resolution_opt -> Clone(ast_pool);
//     return clone;
// }

// void AstIntegerLiteral::Print(LexStream& lex_stream)
// {
//     Coutput << '#' << id << " (IntegerLiteral):  "
//             << lex_stream.NameString(integer_literal_token)
//             << endl;
// }

// void AstLongLiteral::Print(LexStream& lex_stream)
// {
//     Coutput << '#' << id << " (LongLiteral):  "
//             << lex_stream.NameString(long_literal_token)
//             << endl;
// }

// void AstFloatLiteral::Print(LexStream& lex_stream)
// {
//     Coutput << '#' << id << " (FloatLiteral):  "
//             << lex_stream.NameString(float_literal_token)
//             << endl;
// }

// void AstDoubleLiteral::Print(LexStream& lex_stream)
// {
//     Coutput << '#' << id << " (DoubleLiteral):  "
//             << lex_stream.NameString(double_literal_token)
//             << endl;
// }

// void AstTrueLiteral::Print(LexStream& lex_stream)
// {
//     Coutput << '#' << id << " (TrueLiteral):  "
//             << lex_stream.NameString(true_literal_token)
//             << endl;
// }

// void AstFalseLiteral::Print(LexStream& lex_stream)
// {
//     Coutput << '#' << id << " (FalseLiteral):  "
//             << lex_stream.NameString(false_literal_token)
//             << endl;
// }

// void AstStringLiteral::Print(LexStream& lex_stream)
// {
//     Coutput << '#' << id << " (StringLiteral):  "
//             << lex_stream.NameString(string_literal_token)
//             << endl;
// }

// void AstCharacterLiteral::Print(LexStream& lex_stream)
// {
//     Coutput << '#' << id << " (CharacterLiteral):  "
//             << lex_stream.NameString(character_literal_token)
//             << endl;
// }

// void AstNullLiteral::Print(LexStream& lex_stream)
// {
//     Coutput << '#' << id << " (NullLiteral):  "
//             << lex_stream.NameString(null_token)
//             << endl;
// }

// void AstClassLiteral::Print(LexStream& lex_stream)
// {
//     Coutput << '#' << id << " (ClassLiteral):  #" << type -> id << ". "
//             << lex_stream.NameString(class_token) << endl;
//     type -> Print(lex_stream);
// }

// #ifdef HAVE_JIKES_NAMESPACE
// } // Close namespace Jikes block
// #endif
