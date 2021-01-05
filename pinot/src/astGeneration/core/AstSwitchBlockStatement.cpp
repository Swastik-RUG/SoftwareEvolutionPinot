// #include "AstSwitchBlockStatement.h"
// #include "../storage/storagepool.h"
// #include "../../declarations/stream.h"

// #ifdef JIKES_DEBUG
// #endif // JIKES_DEBUG

// #ifdef HAVE_JIKES_NAMESPACE
// namespace Jikes
// { // Open namespace Jikes block
// #endif

// Ast* AstSwitchBlockStatement::Clone(StoragePool* ast_pool)
// {
//     AstSwitchBlockStatement* clone = ast_pool -> GenSwitchBlockStatement();
//     clone -> CloneBlock(ast_pool, this);
//     clone -> AllocateSwitchLabels(NumSwitchLabels());
//     for (unsigned i = 0; i < NumSwitchLabels(); i++)
//         clone -> AddSwitchLabel((AstSwitchLabel*) SwitchLabel(i) ->
//                                 Clone(ast_pool));
//     return clone;
// }

// Ast* AstSwitchBlockStatement::Clone(StoragePool* ast_pool, LexStream& lex_stream)
// {
//     AstSwitchBlockStatement* clone = ast_pool -> GenSwitchBlockStatement();
//     clone -> CloneBlock(ast_pool, this, lex_stream);
//     clone -> AllocateSwitchLabels(NumSwitchLabels());
//     for (unsigned i = 0; i < NumSwitchLabels(); i++)
//         clone -> AddSwitchLabel((AstSwitchLabel*) SwitchLabel(i) ->
//                                 Clone(ast_pool, lex_stream));
//     return clone;
// }

// void AstSwitchBlockStatement::Lexify(LexStream& lex_stream)
// {
// 	for (unsigned i = 0; i < NumSwitchLabels(); i++)
//        	SwitchLabel(i) -> Lexify(lex_stream);
// 	AstBlock::Lexify(lex_stream);
// }


// void AstSwitchBlockStatement::Print()
// {
//     unsigned i;
//     Coutput << '#' << id << " (SwitchBlockStatement): ";
//     for (i = 0; i < NumSwitchLabels(); i++)
//     {
//         if (i % 10 == 0)
//             Coutput << endl << "        ";
//         Coutput << " #" << SwitchLabel(i) -> id << ':';
//     }
//     Coutput << endl;
//     for (i = 0; i < NumSwitchLabels(); i++)
//         SwitchLabel(i) -> Print();
//     AstBlock::Print();
// }


// void AstSwitchBlockStatement::Print(LexStream& lex_stream)
// {
//     unsigned i;
//     Coutput << '#' << id << " (SwitchBlockStatement): ";
//     for (i = 0; i < NumSwitchLabels(); i++)
//     {
//         if (i % 10 == 0)
//             Coutput << endl << "        ";
//         Coutput << " #" << SwitchLabel(i) -> id << ':';
//     }
//     Coutput << endl;
//     for (i = 0; i < NumSwitchLabels(); i++)
//         SwitchLabel(i) -> Print(lex_stream);
//     AstBlock::Print(lex_stream);
// }


// #ifdef HAVE_JIKES_NAMESPACE
// } // Close namespace Jikes block
// #endif
