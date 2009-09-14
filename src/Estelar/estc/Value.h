#pragma once

#include "Node.h"
#include "Atom.h"

namespace est {
	class Value 
	{
	public:
		Value(void);
		~Value(void);
	};

	class AtomValue : public Node, Value {
	public:
		AtomValue(Atom *);
	};
}