#pragma once
#include <stdlib.h>

#include "Token.h"
#include "Constant.h"

namespace est {
	class Parm {
		Token * token;
		Constant * defaultValue;

	public:
//		Parm(Token *);
		Parm(Token * t, Constant * c = NULL) : token(t), defaultValue(c) {};
	};

}