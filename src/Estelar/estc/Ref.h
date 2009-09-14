#pragma once

#include "Node.h"
#include "Atom.h"

namespace est {
	class Ref : public Node
	{
	public:
		Ref(Atom *);
		~Ref(void);

		virtual int generateCode(CodeGenContext * ctx);
	};
}