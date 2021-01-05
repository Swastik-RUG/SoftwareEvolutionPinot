#include "../ast.h"

#ifndef AstSwitchStatement_INCLUDED
#define AstSwitchStatement_INCLUDED

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif
    //
    // SwitchStatement --> <SWITCH, Label_opt, switch_token, Expression, {_token,
    // SwitchBlockStatements, SwitchLabels_opt, }_token>
    //
    class AstSwitchStatement : public AstStatement
    {
        StoragePool *pool;
        //
        // The sorted list of case label values. Index 0 is reserved for the
        // default case. Index 1 - size are for the case labels, and get sorted.
        //
        CaseElement **cases;
        unsigned num_cases;
#ifdef JIKES_DEBUG
        unsigned max_cases; // bounds check only when debugging
#endif                      // JIKES_DEBUG

    public:
        TokenIndex switch_token;
        wchar_t *switch_token_string;
        AstExpression *expression;
        AstBlock *switch_block;

        inline AstSwitchStatement(StoragePool *p)
            : AstStatement(SWITCH), pool(p)
        {
        }
        ~AstSwitchStatement()
        { /*delete switch_token_string;*/
        }

        inline CaseElement *&Case(unsigned i)
        {
            assert(i < num_cases);
            return cases[i + 1];
        }
        inline CaseElement *&DefaultCase() { return cases[0]; }
        inline unsigned NumCases() { return num_cases; }
        void AllocateCases(unsigned estimate = 1);
        inline void AddCase(CaseElement *);

        inline AstSwitchBlockStatement *Block(unsigned i)
        {
            return (AstSwitchBlockStatement *)switch_block->Statement(i);
        }
        inline unsigned NumBlocks() { return switch_block->NumStatements(); }

        void SortCases();
        CaseElement *CaseForValue(i4 value);

#ifdef JIKES_DEBUG
        virtual void Print(LexStream &);
        virtual void Print();
        virtual void Unparse(Ostream &, LexStream *);
#endif // JIKES_DEBUG

        virtual Ast *Clone(StoragePool *);
        virtual Ast *Clone(StoragePool *, LexStream &);
        virtual void Lexify(LexStream &);

        virtual TokenIndex LeftToken() { return switch_token; }
        virtual TokenIndex RightToken()
        {
            return switch_block->right_brace_token;
        }
    };

inline void AstSwitchStatement::AddCase(CaseElement* case_element)
{
    assert(cases);
    cases[++num_cases] = case_element;
#ifdef JIKES_DEBUG
    assert(num_cases < max_cases);
#endif // JIKES_DEBUG
}

inline AstSwitchStatement* Ast::SwitchStatementCast()
{
    return DYNAMIC_CAST<AstSwitchStatement*> (kind == SWITCH ? this : NULL);
}
    

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif