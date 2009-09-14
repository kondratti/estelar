#pragma once

#include "Decl.h"

namespace est {
	class DeclList
	{
	public:
		DeclList(Decl *);

		void Add(Decl *);
		~DeclList(void);
	};
}