#pragma once
#include "stdafx.h"
#include <string>
#include "math.h"
using namespace std;

int getIndex(string const& name)
{
	if (name == "-") return 0;
	else if (name == "!") return 1;
	else if (name == "(") return 2;
	else if (name == ")") return 3;
	else if (name == ",") return 4;
	else if (name == "[") return 5;
	else if (name == "]") return 6;
	else if (name == "{") return 7;
	else if (name == "}") return 8;
	else if (name == "+") return 9;
	else if (name == "=") return 10;
	else if (name == "cos") return 11;
	else if (name == "div") return 12;
	else if (name == "exists") return 13;
	else if (name == "forall") return 14;
	else if (name == "geq") return 15;
	else if (name == "gt") return 16;
	else if (name == "infty") return 17;
	else if (name == "int") return 18;
	else if (name == "leq") return 19;
	else if (name == "lim") return 20;
	else if (name == "log") return 21;
	else if (name == "lt") return 22;
	else if (name == "neq") return 23;
	else if (name == "pm") return 24;
	else if (name == "rightarrow") return 25;
	else if (name == "sin") return 26;
	else if (name == "sqrt") return 27;
	else if (name == "sum") return 28;
	else if (name == "tan") return 29;
	else if (name == "times") return 30;
}

string getName(int index)
{
	switch (index)
	{
		case 0: return "-";
		case 1: return "!";
		case 2: return "(";
		case 3: return ")";
		case 4: return ",";
		case 5: return "[";
		case 6: return "]";
		case 7: return "{";
		case 8: return "}";
		case 9: return "+";
		case 10: return "=";
		case 11: return "cos";
		case 12: return "div";
		case 13: return "exists";
		case 14: return "forall";
		case 15: return "geq";
		case 16: return "gt";
		case 17: return "infty";
		case 18: return "int";
		case 19: return "leq";
		case 20: return "lim";
		case 21: return "log";
		case 22: return "lt";
		case 23: return "neq";
		case 24: return "pm";
		case 25: return "rightarrow";
		case 26: return "sin";
		case 27: return "sqrt";
		case 28: return "sum";
		case 29: return "tan";
		case 30: return "times";
		default: return "fatalError";
	}
}

double sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}