#ifndef Flatten_NAME_H
#define Flatten_NAME_H

#include "declarations/platform.h"
#include "declarations/symbol/symbol.h"
#include "declarations/tuple.h"
#include <vector>

#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes { // Open namespace Jikes block
#endif
class Snapshot;
class StoragePool;

class AstIfStatement;
class AstWhileStatement;
class AstForStatement;
class AstTryStatement;
class AstStatement;
class AstAssignmentExpression;
class AstLocalVariableStatement;
class AstReturnStatement;
class AstMethodInvocation;
class AstSynchronizedStatement;
class AstConditionalExpression;

#include <set>

class Flatten
{
	friend class SingletonAnalysis;
	friend class FactoryAnalysis;
	friend class ChainAnalysis;
	private:
		vector<Ast*> statements;
		vector<AstExpression*> conditions;
		AstExpression *condition;
		vector<Snapshot*> summary;
		vector<Snapshot*> traces;
		MethodSymbol *method;
		bool capture_trace;
		StoragePool *ast_pool;
		set<signed> pred;
		bool multi_if;
	public:
		enum TransitionTag
		{
			UNCONDITIONAL,
			CONDITIONAL,
			NOTRANSITION
		};
		Flatten():condition(NULL), capture_trace(false), multi_if(false){ pred.insert(-1); }
		Flatten(MethodSymbol *msym, StoragePool *pool):condition(NULL),method(msym),capture_trace(false),ast_pool(pool), multi_if(false){ pred.insert(-1); }
		~Flatten(){}
		void init(MethodSymbol *msym, StoragePool *pool){ method = msym; ast_pool = pool; }
		void BuildSummary();
		void UpdateSummary();
		void DumpSummary();
		void PushCondition(AstExpression*);
		void PopCondition();
		bool Compare(AstExpression *, AstExpression *);
		void FlattenBoolean(vector<AstExpression*>&, AstExpression*);
		TransitionTag TransitionFlow(AstExpression *, AstExpression *);
		void visit(AstBlock*);
		void visit(AstIfStatement*);
		void visit(AstWhileStatement*);
		void visit(AstForStatement*);
		void visit(AstTryStatement*);
		void visit(AstStatement*);
		void visit(AstExpression*);
		void visit(AstAssignmentExpression*);
		void visit(AstLocalVariableStatement*);
		void visit(AstVariableDeclarator*);
		void visit(AstReturnStatement*);
		void visit(AstMethodInvocation*);
		void visit(AstSynchronizedStatement*);
		void visit(AstConditionalExpression*);
};

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif