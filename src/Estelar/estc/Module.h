#pragma once

#include <list>

#include "DeclList.h"

namespace est {
	class Module {
	public:
		Module(std::list<Decl *> *);
	};
}