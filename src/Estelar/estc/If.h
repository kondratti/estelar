#pragma once

#include <list>
#include "Node.h"
#include "Statement.h"

namespace est {
	class If : public Statement
	{
	public:
		If(Node * test, std::list<Statement *> * t, std::list<Statement *> * f, int line);
		virtual void generateCode(CodeGenContext *);
	};
}