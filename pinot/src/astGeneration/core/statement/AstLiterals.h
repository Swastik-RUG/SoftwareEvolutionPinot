// #include "../ast.h"

// #ifndef AstLiterals_INCLUDED
// #define AstLiterals_INCLUDED

// #ifdef HAVE_JIKES_NAMESPACE
// namespace Jikes
// { // Open namespace Jikes block
// #endif

//     class AstExpression;

//     //
//     // Represents an int literal.
//     //
//     class AstIntegerLiteral : public AstExpression
//     {
//     public:
//         TokenIndex integer_literal_token;
//         wchar_t *integer_literal_token_string;

//         inline AstIntegerLiteral(TokenIndex token)
//             : AstExpression(INTEGER_LITERAL), integer_literal_token(token)
//         {
//         }
//         ~AstIntegerLiteral()
//         { /*delete integer_literal_token_string;*/
//         }

// #ifdef JIKES_DEBUG
//         virtual void Print(LexStream &);
//         virtual void Print();
//         virtual void Unparse(Ostream &, LexStream *);
// #endif // JIKES_DEBUG

//         virtual Ast *Clone(StoragePool *);
//         virtual Ast *Clone(StoragePool *, LexStream &);
//         virtual void Lexify(LexStream &);

//         virtual TokenIndex LeftToken() { return integer_literal_token; }
//         virtual TokenIndex RightToken() { return integer_literal_token; }
//     };

//     //
//     // LongLiteral --> <LONG_LITERAL, long_literal_token, value>
//     //
//     class AstLongLiteral : public AstExpression
//     {
//     public:
//         TokenIndex long_literal_token;
//         wchar_t *long_literal_token_string;

//         inline AstLongLiteral(TokenIndex token)
//             : AstExpression(LONG_LITERAL), long_literal_token(token)
//         {
//         }
//         ~AstLongLiteral()
//         { /*delete long_literal_token_string;*/
//         }

// #ifdef JIKES_DEBUG
//         virtual void Print(LexStream &);
//         virtual void Print();
//         virtual void Unparse(Ostream &, LexStream *);
// #endif // JIKES_DEBUG

//         virtual Ast *Clone(StoragePool *);
//         virtual Ast *Clone(StoragePool *, LexStream &);
//         virtual void Lexify(LexStream &);

//         virtual TokenIndex LeftToken() { return long_literal_token; }
//         virtual TokenIndex RightToken() { return long_literal_token; }
//     };

//     //
//     // FloatLiteral --> <FLOAT_LITERAL, Literal, value>
//     //
//     class AstFloatLiteral : public AstExpression
//     {
//     public:
//         TokenIndex float_literal_token;
//         wchar_t *float_literal_token_string;

//         inline AstFloatLiteral(TokenIndex token)
//             : AstExpression(FLOAT_LITERAL), float_literal_token(token)
//         {
//         }
//         ~AstFloatLiteral()
//         { /*delete float_literal_token_string;*/
//         }

// #ifdef JIKES_DEBUG
//         virtual void Print(LexStream &);
//         virtual void Print();
//         virtual void Unparse(Ostream &, LexStream *);
// #endif // JIKES_DEBUG

//         virtual Ast *Clone(StoragePool *);
//         virtual Ast *Clone(StoragePool *, LexStream &);
//         virtual void Lexify(LexStream &);

//         virtual TokenIndex LeftToken() { return float_literal_token; }
//         virtual TokenIndex RightToken() { return float_literal_token; }
//     };

//     //
//     // DoubleLiteral --> <DOUBLE_LITERAL, Literal, value>
//     //
//     class AstDoubleLiteral : public AstExpression
//     {
//     public:
//         TokenIndex double_literal_token;
//         wchar_t *double_literal_token_string;

//         inline AstDoubleLiteral(TokenIndex token)
//             : AstExpression(DOUBLE_LITERAL), double_literal_token(token)
//         {
//         }
//         ~AstDoubleLiteral()
//         { /*delete double_literal_token_string;*/
//         }

// #ifdef JIKES_DEBUG
//         virtual void Print(LexStream &);
//         virtual void Print();
//         virtual void Unparse(Ostream &, LexStream *);
// #endif // JIKES_DEBUG

//         virtual Ast *Clone(StoragePool *);
//         virtual Ast *Clone(StoragePool *, LexStream &);
//         virtual void Lexify(LexStream &);

//         virtual TokenIndex LeftToken() { return double_literal_token; }
//         virtual TokenIndex RightToken() { return double_literal_token; }
//     };

//     //
//     // TrueLiteral --> <TRUE_LITERAL, Literal, value>
//     //
//     class AstTrueLiteral : public AstExpression
//     {
//     public:
//         TokenIndex true_literal_token;
//         wchar_t *true_literal_token_string;

//         inline AstTrueLiteral(TokenIndex token)
//             : AstExpression(TRUE_LITERAL), true_literal_token(token)
//         {
//         }
//         ~AstTrueLiteral()
//         { /*delete true_literal_token_string;*/
//         }

// #ifdef JIKES_DEBUG
//         virtual void Print(LexStream &);
//         virtual void Print();
//         virtual void Unparse(Ostream &, LexStream *);
// #endif // JIKES_DEBUG

//         virtual Ast *Clone(StoragePool *);
//         virtual Ast *Clone(StoragePool *, LexStream &);
//         virtual void Lexify(LexStream &);

//         virtual TokenIndex LeftToken() { return true_literal_token; }
//         virtual TokenIndex RightToken() { return true_literal_token; }
//     };

//     //
//     // FalseLiteral --> <FALSE_LITERAL, Literal, value>
//     //
//     class AstFalseLiteral : public AstExpression
//     {
//     public:
//         TokenIndex false_literal_token;
//         wchar_t *false_literal_token_string;

//         inline AstFalseLiteral(TokenIndex token)
//             : AstExpression(FALSE_LITERAL), false_literal_token(token)
//         {
//         }
//         ~AstFalseLiteral()
//         { /*delete false_literal_token_string;*/
//         }

// #ifdef JIKES_DEBUG
//         virtual void Print(LexStream &);
//         virtual void Print();
//         virtual void Unparse(Ostream &, LexStream *);
// #endif // JIKES_DEBUG

//         virtual Ast *Clone(StoragePool *);
//         virtual Ast *Clone(StoragePool *, LexStream &);
//         virtual void Lexify(LexStream &);

//         virtual TokenIndex LeftToken() { return false_literal_token; }
//         virtual TokenIndex RightToken() { return false_literal_token; }
//     };

//     //
//     // StringLiteral --> <STRING_LITERAL, Literal, value>
//     //
//     class AstStringLiteral : public AstExpression
//     {
//     public:
//         TokenIndex string_literal_token;
//         wchar_t *string_literal_token_string;

//         inline AstStringLiteral(TokenIndex token)
//             : AstExpression(STRING_LITERAL), string_literal_token(token)
//         {
//         }
//         ~AstStringLiteral()
//         { /*delete string_literal_token_string;*/
//         }

// #ifdef JIKES_DEBUG
//         virtual void Print(LexStream &);
//         virtual void Print();
//         virtual void Unparse(Ostream &, LexStream *);
// #endif // JIKES_DEBUG

//         virtual Ast *Clone(StoragePool *);
//         virtual Ast *Clone(StoragePool *, LexStream &);
//         virtual void Lexify(LexStream &);

//         virtual TokenIndex LeftToken() { return string_literal_token; }
//         virtual TokenIndex RightToken() { return string_literal_token; }
//     };

//     //
//     // CharacterLiteral --> <CHARACTER_LITERAL, literal_token, value>
//     //
//     class AstCharacterLiteral : public AstExpression
//     {
//     public:
//         TokenIndex character_literal_token;
//         wchar_t *character_literal_token_string;

//         inline AstCharacterLiteral(TokenIndex token)
//             : AstExpression(CHARACTER_LITERAL), character_literal_token(token)
//         {
//         }
//         ~AstCharacterLiteral()
//         { /*delete character_literal_token_string;*/
//         }

// #ifdef JIKES_DEBUG
//         virtual void Print(LexStream &);
//         virtual void Print();
//         virtual void Unparse(Ostream &, LexStream *);
// #endif // JIKES_DEBUG

//         virtual Ast *Clone(StoragePool *);
//         virtual Ast *Clone(StoragePool *, LexStream &);
//         virtual void Lexify(LexStream &);

//         virtual TokenIndex LeftToken() { return character_literal_token; }
//         virtual TokenIndex RightToken() { return character_literal_token; }
//     };

//     //
//     // NullLiteral --> <NULL_EXPRESSION, null_token>
//     //
//     class AstNullLiteral : public AstExpression
//     {
//     public:
//         TokenIndex null_token;
//         wchar_t *null_token_string;

//         inline AstNullLiteral(TokenIndex token)
//             : AstExpression(NULL_LITERAL), null_token(token)
//         {
//         }
//         ~AstNullLiteral()
//         { /*delete null_token_string;*/
//         }

// #ifdef JIKES_DEBUG
//         virtual void Print(LexStream &);
//         virtual void Print();
//         virtual void Unparse(Ostream &, LexStream *);
// #endif // JIKES_DEBUG

//         virtual Ast *Clone(StoragePool *);
//         virtual Ast *Clone(StoragePool *, LexStream &);
//         virtual void Lexify(LexStream &);

//         virtual TokenIndex LeftToken() { return null_token; }
//         virtual TokenIndex RightToken() { return null_token; }
//     };

//     //
//     // Represents class literals.
//     //
//     class AstClassLiteral : public AstExpression
//     {
//     public:
//         AstType *type;
//         TokenIndex class_token;
//         wchar_t *class_token_string;

//         //
//         // If this expression requires a caching variable and a call to class$(),
//         // the resolution holds the needed class$xxx or array$xxx cache.
//         //
//         AstExpression *resolution_opt;

//         inline AstClassLiteral(TokenIndex token)
//             : AstExpression(CLASS_LITERAL), class_token(token)
//         {
//         }
//         ~AstClassLiteral()
//         { /*delete class_token_string;*/
//         }

// #ifdef JIKES_DEBUG
//         virtual void Print(LexStream &);
//         virtual void Print();
//         virtual void Unparse(Ostream &, LexStream *);
// #endif // JIKES_DEBUG

//         virtual Ast *Clone(StoragePool *);
//         virtual Ast *Clone(StoragePool *, LexStream &);
//         virtual void Lexify(LexStream &);

//         virtual TokenIndex LeftToken() { return type->LeftToken(); }
//         virtual TokenIndex RightToken() { return class_token; }
//     };

// #ifdef HAVE_JIKES_NAMESPACE
// } // Close namespace Jikes block
// #endif

// #endif
