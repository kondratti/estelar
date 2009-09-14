#pragma once

//#include "Value.h"
#include "Atom.h"
#include "CodeGenContext.h"

namespace est {

	class Value;

	class Node {

		virtual int generateCode(CodeGenContext *) = 0;
	};

	class BinaryOpNode  : public Node {

	public: 
		BinaryOpNode  (Node *, Node *, int ln);
		virtual int generateCode(CodeGenContext * ctx);
	};

	class Plus : public BinaryOpNode {
	public: 
		Plus(Node * l, Node * r, int ln) : BinaryOpNode(l,r,ln) {};
		virtual int generateCode(CodeGenContext * ctx);
	};

	class Minus : public BinaryOpNode {
	public: 
		Minus(Node * l, Node * r, int ln) : BinaryOpNode(l,r,ln) {};
		virtual int generateCode(CodeGenContext * ctx);
	};

	class Times : public BinaryOpNode {
	public: 
		Times(Node * l, Node * r, int ln) : BinaryOpNode(l,r,ln) {};
		virtual int generateCode(CodeGenContext * ctx);
	};

	class Divide : public BinaryOpNode {
	public: 
		Divide(Node * l, Node * r, int ln) : BinaryOpNode(l,r,ln) {};
		virtual int generateCode(CodeGenContext * ctx);
	};

	class Mod : public BinaryOpNode {
	public: 
		Mod(Node * l, Node * r, int ln) : BinaryOpNode(l,r,ln) {};
		virtual int generateCode(CodeGenContext * ctx);
	};

	class GT : public BinaryOpNode {
	public: 
		GT(Node * l, Node * r, int ln) : BinaryOpNode(l,r,ln) {};
		virtual int generateCode(CodeGenContext * ctx);
	};

	class PrePlusPlus : public Node {
	public: 
		PrePlusPlus(Atom * l);
		virtual int generateCode(CodeGenContext * ctx);
	};

	class ValueNode : public Node {
	public: 
		ValueNode(Value * l);
		ValueNode(Atom * l);
		virtual int generateCode(CodeGenContext * ctx);
	};

}