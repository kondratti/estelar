#pragma once
#include <string>

namespace est {
	class Token {
	public:
		std::string text;
		unsigned int lineno;
	};
}