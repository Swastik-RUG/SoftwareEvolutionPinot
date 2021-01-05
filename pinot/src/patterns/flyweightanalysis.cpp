#include "./FlyweightAnalysis.h"
#include "../astGeneration/ast.h"
#include "../astGeneration/core/statement/AstWhileStatement.h"
#include "../astGeneration/core/statement/AstForStatement.h"


#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes { // Open namespace Jikes block
#endif

void FlyweightAnalysis::visit(AstBlock* block)
{
	if (block->NumStatements())
	{
		unsigned lstmt = (block->NumStatements() == 1) ? 0 : (block->NumStatements() - 1);
		for (unsigned i = 0; i < lstmt; i++) visit(block -> Statement(i));
		visit(block->Statement(lstmt));
		UpdateSummary();
	}
}
void FlyweightAnalysis::visit(AstWhileStatement* while_statement)
{
	visit(while_statement->statement);
}
void FlyweightAnalysis::visit(AstForStatement* for_statement)
{
	UpdateSummary();
	conditions.push_back(for_statement->end_expression_opt);
	visit(for_statement->statement);
	UpdateSummary();
	conditions.pop_back();
}
void FlyweightAnalysis::visit(AstTryStatement* try_statement)
{
	visit(try_statement->block);
}
void FlyweightAnalysis::visit(AstStatement *statement)
{
	switch(statement -> kind)
	{
		case Ast::IF:
			visit(statement -> IfStatementCast());
			break;
		case Ast::WHILE:
			visit(statement -> WhileStatementCast());
			break;
		case Ast::FOR:
			visit(statement -> ForStatementCast());
			break;
		case Ast::TRY:
			visit(statement -> TryStatementCast());
			break;
		case Ast::EXPRESSION_STATEMENT:
			visit(statement -> ExpressionStatementCast() -> expression);
			break;
		case Ast::SYNCHRONIZED_STATEMENT:
			visit(statement -> SynchronizedStatementCast());
			break;
		case Ast::BLOCK:
			visit(statement -> BlockCast());
			break;
		case Ast::RETURN:
			visit(statement -> ReturnStatementCast());
			break;
		case Ast::LOCAL_VARIABLE_DECLARATION:
			visit(statement -> LocalVariableStatementCast());
			break;
		default:
			break;
	}
}
void FlyweightAnalysis::visit(AstExpression *expression)
{
	switch(expression -> kind)
	{
		case Ast::PARENTHESIZED_EXPRESSION:
			visit(expression->ParenthesizedExpressionCast() -> expression);
			break;
		case Ast::CAST:
			visit(expression->CastExpressionCast() -> expression);
			break;
		case Ast::CONDITIONAL:
			visit(expression->ConditionalExpressionCast());
			break;
		case Ast::ASSIGNMENT:
			visit(expression->AssignmentExpressionCast());
			break;
		case Ast::CALL:
			visit(expression->MethodInvocationCast());
			break;
		default:
			break;
	}
}
void FlyweightAnalysis::visit(AstMethodInvocation* call)
{
	// might want to check all participants in this method invocationo
	// e.g., base_opt, 	call->symbol->MethodCast()>Type(), call->arguments->Argument(i), etc

	if (call->NumArguments() > 1)
	{
		AstExpression *expression = *&call->arguments->Argument(1);
		expression = (expression->kind == Ast::CAST) ? expression->CastExpressionCast()->expression : expression;
		if (expression->symbol->VariableCast() && (expression->symbol->VariableCast()->Type() == flyweight))
		{
			statements.push_back(call);
		}
	}
}
void FlyweightAnalysis::visit(AstIfStatement* statement)
{
	UpdateSummary();
	conditions.push_back(statement->expression);
	visit(statement->expression);
	visit(statement->true_statement);
	UpdateSummary();
	conditions.pop_back();
	if (statement->false_statement_opt)
		visit(statement->false_statement_opt);
}
void FlyweightAnalysis::visit(AstAssignmentExpression *expression)
{
	if (expression->left_hand_side->symbol->VariableCast()
	&& (expression->left_hand_side->symbol->VariableCast()->Type() == flyweight))
		statements.push_back(expression);
	else if (expression->left_hand_side->symbol->TypeCast()
	&& (expression->left_hand_side->symbol->TypeCast() == flyweight))
		statements.push_back(expression);
	// TODO also check for aliasing
}
void FlyweightAnalysis::visit(AstLocalVariableStatement* local_var)
{
	if (local_var->type->symbol == flyweight)
	{
		for (unsigned i=0; i < local_var->NumVariableDeclarators(); i++)
			visit(local_var->VariableDeclarator(i));
	}
}
void FlyweightAnalysis::visit(AstVariableDeclarator* var_declarator)
{
	if (var_declarator->variable_initializer_opt && (var_declarator->symbol->Type() == flyweight))
		statements.push_back(var_declarator);
}
void FlyweightAnalysis::visit(AstReturnStatement* statement)
{
	if (statement->expression_opt)
	{
		if (statement->expression_opt->symbol->VariableCast()
		&& (statement->expression_opt->symbol->VariableCast()->Type() == flyweight))
			statements.push_back(statement);
		else if (statement->expression_opt->symbol->TypeCast()
		&& (statement->expression_opt->symbol->TypeCast() == flyweight))
			statements.push_back(statement);
	}
}
void FlyweightAnalysis::UpdateSummary()
{
	if (statements.size())
	{
		Snapshot *snapshot = new Snapshot();
		snapshot->statements = new vector<Ast*>(statements);
		statements.clear();
		if (conditions.size())
		{
			snapshot->conditions = new vector<AstExpression*>(conditions);
		}
		snapshot->index = summary.size();
		summary.push_back(snapshot);
	}
}
void FlyweightAnalysis::DumpSummary()
{
	Coutput << GetFlyweight->Utf8Name() << endl;
	for (unsigned i = 0; i < summary.size(); i++)
	{
		Snapshot *snapshot = summary[i];
		Coutput << "Snapshot[" << i << "]" << endl;
		Coutput << "STATEMENTS:" << endl;
		unsigned j;
		for (j = 0; j < snapshot->statements->size(); j++)
		{
			if ((*snapshot->roles)[j]->vsym)
				Coutput << (*snapshot->roles)[j]->vsym->Utf8Name();
			else
				Coutput << (*snapshot->roles)[j]->array_access->base->symbol->VariableCast()->Utf8Name()
					<< "[" << (*snapshot->roles)[j]->array_access->expression->symbol->VariableCast()->Utf8Name() << "]";
			Coutput << ": " << (*snapshot->roles)[j]->TagName() << endl;
			(*snapshot->statements)[j]->Print();
		}
		Coutput << "CONDITIONS:" << endl;
		if (snapshot->conditions)
		{
			for (j = 0; j < snapshot->conditions->size(); j++)
				(*snapshot->conditions)[j]->Print();
		}
		Coutput << endl;
	}
}


#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif
