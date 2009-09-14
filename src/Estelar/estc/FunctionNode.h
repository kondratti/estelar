#pragma once

#include <list>

#include "Decl.h"
#include "Token.h"
#include "ParmList.h"
#include "Node.h"
#include "Statement.h"

namespace est {
	class FunctionNode : public Decl {

	public:
		//FunctionNode(Token * t, std::list<Parm *> *, std::list<Statement *> *) : Decl(t) {};
	};
}