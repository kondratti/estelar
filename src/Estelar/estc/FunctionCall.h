#pragma once

#include <list>

#include "Statement.h"
#include "Node.h"
#include "Atom.h"
#include "Token.h"

namespace est {
	class FunctionCall : public Node
	{
	public:
		FunctionCall(Node *, std::list<Node *> * parms);
		FunctionCall(Atom *, std::list<Node *> * parms);
		virtual int generateCode(CodeGenContext * ctx);
	};
}