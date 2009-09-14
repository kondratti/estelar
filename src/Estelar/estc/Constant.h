#pragma once

#include "Value.h"
#include "Token.h"

namespace est {
	class Constant : public Value {
		Token * tok;
	public:
		Constant();
	};

	class FloatConstant : public Constant {
	public:
		FloatConstant(Token *);
	};

	class StringConstant : public Constant {
	public:
		StringConstant(Token *);
	};

	class IntConstant : public Constant {
	public:
		IntConstant(Token *);
	};
}