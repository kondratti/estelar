#pragma once
#include <list>
#include "Constant.h"
#include "Parm.h"
#include "Statement.h"

namespace est {
	class Closure : public Constant
	{
	public:
		Closure(std::list<est::Parm *> *, std::list<est::Statement*> *);
		~Closure(void);
	};
}