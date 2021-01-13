#ifndef ControlAnalysis_NAME_H
#define ControlAnalysis_NAME_H

#include "../platform/platform.h"
#include "../symbol/symbol.h"
#include "../tuple.h"
#include <vector>


#ifdef HAVE_JIKES_NAMESPACE
namespace Jikes { // Open namespace Jikes block
#endif

class AstExpression;
class AstIfStatement;
class AstWhileStatement;
class AstForStatement;
class AstStatement;
class AstSynchronizedStatement;
class AstConditionalExpression;
// template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
// class vector: protected _Vector_base<_Tp, _Alloc>;

class ControlAnalysis
{
	private:
		AstExpression *expression;
	public:
		ControlAnalysis(AstExpression *e)
			: expression (e), flag(false), cond(0), containing_stmt(0), result (false) {}
		void visit(AstBlock*);
		void visit(AstIfStatement*);
		void visit(AstWhileStatement*);
		void visit(AstForStatement*);
		void visit(AstStatement*);
		void visit(AstExpression*);
		void visit(AstSynchronizedStatement*);
		void visit(AstConditionalExpression*);
		bool IsConditional();
		bool IsRepeated();
		bool IsSynchronized();		
		~ControlAnalysis(){}
		bool flag;
		AstExpression* cond;
		Ast* containing_stmt;
		bool result;
		std::vector<Ast*> rt_stack;
};

#ifdef HAVE_JIKES_NAMESPACE
} // Close namespace Jikes block
#endif

#endif