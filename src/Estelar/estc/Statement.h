#pragma once

#include "Node.h"

namespace est {
	class Statement
	{
		int lineNo;
	public:
		Statement(int l) : lineNo(l) {};
		Statement(Node *);
		virtual void generateCode(CodeGenContext *);
	};
}