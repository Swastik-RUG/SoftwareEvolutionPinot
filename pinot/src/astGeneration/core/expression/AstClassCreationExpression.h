#include "../../ast.h"

#ifndef AstClassCreationExpression_INCLUDED
#define AstClassCreationExpression_INCLUDED

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes
{ // Open namespace Jikes block
#endif

    //
    // ClassCreationExpression represents a class instance creation (keyword new,
    // including anonymous classes). Also see ArrayCreationExpression. Sometimes,
    // during semantic analysis an artificial base_opt expression is constructed.
    // In such a case, the user can determine this condition by testing
    // base_opt -> generated.
    //
    class AstClassCreationExpression : public AstExpression
    {
    public:
        AstExpression *base_opt;
        TokenIndex new_token;
        wchar_t *new_token_string;
        AstTypeArguments *type_arguments_opt;
        AstTypeName *class_type;
        AstArguments *arguments;
        AstClassBody *class_body_opt;

        //
        // For anonymous classes, we resolve the original statement into a new
        // one that does not have a class_body_opt. This is necessary to get
        // the parameters called in the correct order.
        //
        AstClassCreationExpression *resolution_opt;

        inline AstClassCreationExpression()
            : AstExpression(CLASS_CREATION)
        {
        }
        ~AstClassCreationExpression()
        { /*delete new_token_string;*/
        }

        virtual void PrintAssociation(AssocTable *, wchar_t *, wchar_t *, wchar_t *, LexStream &);

#ifdef JIKES_DEBUG
        virtual void Print(LexStream &);
        virtual void Print();
        virtual void Unparse(Ostream &, LexStream *);
#endif // JIKES_DEBUG

        virtual Ast *Clone(StoragePool *);
        virtual Ast *Clone(StoragePool *, LexStream &);
        virtual void Lexify(LexStream &);

        virtual TokenIndex LeftToken()
        {
            return base_opt ? base_opt->LeftToken() : new_token;
        }
        virtual TokenIndex RightToken()
        {
            return class_body_opt ? class_body_opt->right_brace_token
                                  : arguments->right_parenthesis_token;
        }
        virtual void Accept(CreationAnalysis &visitor) { visitor.visit(this); }
    };

inline AstClassCreationExpression* Ast::ClassCreationExpressionCast()
{
    return DYNAMIC_CAST<AstClassCreationExpression*>
        (kind == CLASS_CREATION ? this : NULL);
}

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif
