
#include "AstSwitchStatement.h"
#include "../../storage/storagepool.h"
#include "../../../declarations/stream.h"

#ifdef JIKES_DEBUG
#endif // JIKES_DEBUG

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

void AstSwitchStatement::AllocateCases(unsigned estimate)
{
    //
    // Add one to the estimate to save room for the default case in element 0.
    //
    assert(! cases);
    cases = new (pool -> Alloc((estimate + 1) * sizeof(CaseElement*)))
        CaseElement*[estimate + 1];
#ifdef JIKES_DEBUG
    max_cases = estimate + 1;
#endif // JIKES_DEBUG
}


//
// This procedure uses a quick sort algorithm to sort the cases in a switch
// statement. Element 0 is not sorted, because it is the default case (and
// may be NULL).
//
void AstSwitchStatement::SortCases()
{
    int lower;
    int upper;
    int lostack[32];
    int histack[32];
    int top = 0;
    int i;
    int j;
    CaseElement pivot;
    CaseElement temp;

    lostack[top] = 1;
    histack[top] = num_cases;

    while (top >= 0)
    {
        lower = lostack[top];
        upper = histack[top];
        top--;

        while (upper > lower)
        {
            //
            // The array is most-likely almost sorted. Therefore,
            // we use the middle element as the pivot element.
            //
            i = (lower + upper) >> 1;
            pivot = *cases[i];
            *cases[i] = *cases[lower];

            //
            // Split the array section indicated by LOWER and UPPER
            // using ARRAY(LOWER) as the pivot.
            //
            i = lower;
            for (j = lower + 1; j <= upper; j++)
                if (*cases[j] < pivot)
                {
                    temp = *cases[++i];
                    *cases[i] = *cases[j];
                    *cases[j] = temp;
                }
            *cases[lower] = *cases[i];
            *cases[i] = pivot;

            top++;
            if ((i - lower) < (upper - i))
            {
                lostack[top] = i + 1;
                histack[top] = upper;
                upper = i - 1;
            }
            else
            {
                histack[top] = i - 1;
                lostack[top] = lower;
                lower = i + 1;
            }
        }
    }
}


//
// Performs a binary search to locate the correct case (including the
// default case) for a constant expression value. Returns NULL if the switch
// is a no-op for this constant.
//
CaseElement* AstSwitchStatement::CaseForValue(i4 value)
{
    unsigned lower = 1;
    unsigned upper = num_cases;
    while (lower <= upper)
    {
        unsigned mid = (lower + upper) >> 1;
        CaseElement* elt = cases[mid];
        if (elt -> value == value)
            return elt;
        if (elt -> value > value)
            upper = mid - 1;
        else
            lower = mid + 1;
    }
    return cases[0];
}

Ast* AstSwitchStatement::Clone(StoragePool* ast_pool)
{
    AstSwitchStatement* clone = ast_pool -> GenSwitchStatement();
    clone -> switch_token = switch_token;

    clone -> switch_token_string = switch_token_string;

    clone -> expression = (AstExpression*) expression -> Clone(ast_pool);
    clone -> switch_block = (AstBlock*) switch_block -> Clone(ast_pool);
    clone -> AllocateCases(NumCases());
    if (DefaultCase())
    {
        clone -> DefaultCase() = ast_pool -> GenCaseElement(0, 0);
        *clone -> DefaultCase() = *DefaultCase();
    }
    for (unsigned i = 0; i < NumCases(); i++)
    {
        CaseElement* elt = ast_pool -> GenCaseElement(0, 0);
        *elt = *Case(i);
        clone -> AddCase(elt);
    }
    return clone;
}

Ast* AstSwitchStatement::Clone(StoragePool* ast_pool, LexStream& lex_stream)
{
    AstSwitchStatement* clone = ast_pool -> GenSwitchStatement();
    clone -> switch_token = switch_token;
    clone -> expression = (AstExpression*) expression -> Clone(ast_pool, lex_stream);
    clone -> switch_block = (AstBlock*) switch_block -> Clone(ast_pool, lex_stream);
    clone -> AllocateCases(NumCases());
    if (DefaultCase())
    {
        clone -> DefaultCase() = ast_pool -> GenCaseElement(0, 0);
        *clone -> DefaultCase() = *DefaultCase();
    }
    for (unsigned i = 0; i < NumCases(); i++)
    {
        CaseElement* elt = ast_pool -> GenCaseElement(0, 0);
        *elt = *Case(i);
        clone -> AddCase(elt);
    }


    clone -> switch_token_string = new wchar_t[wcslen(lex_stream.NameString(switch_token)) + 1];
    wcscpy(clone -> switch_token_string, lex_stream.NameString(switch_token));


    clone -> switch_token_string = const_cast<wchar_t*>(lex_stream.NameString(switch_token));

    return clone;
}

void AstSwitchStatement::Lexify(LexStream& lex_stream)
{
	expression -> Lexify(lex_stream);
	switch_block -> Lexify(lex_stream);

	switch_token_string = const_cast<wchar_t*>(lex_stream.NameString(switch_token));
}

void AstSwitchStatement::Print()
{
    Coutput << '#' << id << " (SwitchStatement):  "
            << switch_token_string
            << " ( #" << expression -> id << " ) #" << switch_block -> id
            << endl;
    for (unsigned i = 0; i <= num_cases; i++)
    {
        Coutput << " case index: " << i;
        if (cases[i])
            Coutput << "  block: " << cases[i] -> block_index
                    << "  label: " << cases[i] -> case_index
                    << "  value: " << cases[i] -> value << endl;
        else Coutput << "(none)" << endl;
    }
    expression -> Print();
    switch_block -> Print();
}

void AstSwitchStatement::Print(LexStream& lex_stream)
{
    Coutput << '#' << id << " (SwitchStatement):  "
            << lex_stream.NameString(switch_token)
            << " ( #" << expression -> id << " ) #" << switch_block -> id
            << endl;
    for (unsigned i = 0; i <= num_cases; i++)
    {
        Coutput << " case index: " << i;
        if (cases[i])
            Coutput << "  block: " << cases[i] -> block_index
                    << "  label: " << cases[i] -> case_index
                    << "  value: " << cases[i] -> value << endl;
        else Coutput << "(none)" << endl;
    }
    expression -> Print(lex_stream);
    switch_block -> Print(lex_stream);
}

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif
