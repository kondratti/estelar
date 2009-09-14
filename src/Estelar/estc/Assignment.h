#pragma once

#include "Statement.h"
#include "Atom.h"
#include "Node.h"
#include "Value.h"

namespace est {
	class Assignment : public Statement
	{
	public:

		Assignment(Atom *, Node *);
		Assignment(Atom *, Value *);
		virtual void generateCode(CodeGenContext *);
	};

	class AssignmentPlus : public Assignment {
	public:
		AssignmentPlus(Atom *, Node *);
	};

	class AssignmentMinus : public Assignment {
	public:
		AssignmentMinus(Atom *, Node *);
	};
}