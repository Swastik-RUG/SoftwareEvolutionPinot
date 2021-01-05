// #include "../ast.h"
// #include "../storage/storagepool.h"
// #include "../../declarations/stream.h"

// #ifndef AstSwitchBlockStatement_INCLUDED
// #define AstSwitchBlockStatement_INCLUDED

// #ifdef HAVE_JIKES_NAMESPACE
// namespace Jikes
// { // Open namespace Jikes block
// #endif

// //
// // SwitchBlockStatement --> <SWITCH_BLOCK, SwitchLabels, BlockStatements>
// //
// class AstSwitchBlockStatement : public AstBlock
// {
//     AstArray<AstSwitchLabel*>* switch_labels;

// public:
//     inline AstSwitchBlockStatement(StoragePool* p)
//         : AstBlock(p, SWITCH_BLOCK)
//     {
//         no_braces = true;
//     }
//     ~AstSwitchBlockStatement() {}

//     inline AstSwitchLabel*& SwitchLabel(unsigned i)
//     {
//         return (*switch_labels)[i];
//     }
//     inline unsigned NumSwitchLabels()
//     {
//         return switch_labels ? switch_labels -> Length() : 0;
//     }
//     inline void AllocateSwitchLabels(unsigned estimate = 1);
//     inline void AddSwitchLabel(AstSwitchLabel*);

// #ifdef JIKES_DEBUG
//     virtual void Print(LexStream&);
//     virtual void Print();
//     virtual void Unparse(Ostream&, LexStream*);
// #endif // JIKES_DEBUG

//     virtual Ast* Clone(StoragePool*);
//     virtual Ast* Clone(StoragePool*, LexStream&);
//     virtual void Lexify(LexStream&);

//     virtual TokenIndex LeftToken() { return SwitchLabel(0) -> case_token; }
//     // Inherited RightToken() is adequate.
// };

// inline AstSwitchBlockStatement* Ast::SwitchBlockStatementCast()
// {
//     return DYNAMIC_CAST<AstSwitchBlockStatement*>
//         (kind == SWITCH_BLOCK ? this : NULL);
// }

// void AstSwitchBlockStatement::AllocateSwitchLabels(unsigned estimate)
// {
//     assert(! switch_labels);
//     switch_labels = new (pool) AstArray<AstSwitchLabel*> (pool, estimate);
// }

// void AstSwitchBlockStatement::AddSwitchLabel(AstSwitchLabel* case_label)
// {
//     assert(switch_labels);
//     switch_labels -> Next() = case_label;
// }


// #ifdef HAVE_JIKES_NAMESPACE
// } // Close namespace Jikes block
// #endif

// #endif
