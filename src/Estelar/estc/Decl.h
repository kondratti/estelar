#pragma once

#include "Value.h"
#include "Token.h"

namespace est {
	class Decl {
		Token * token;
	public:
		Decl(Token *t, Value *) : token(t) {};
		int lineNo()	{return token->lineno;};
	};
}