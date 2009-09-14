#pragma once

#include "Atom.h"
#include "Node.h"

namespace est {
	class WeakRef : public Node
	{
	public:
		WeakRef(Atom *);
		~WeakRef(void);
		virtual int generateCode(CodeGenContext * ctx);
	};
}