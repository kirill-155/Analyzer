#pragma once
#include "Node.h"
#include "Hash_table.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Syntactic_analysis
{
private:
	string lexeme, type_lexeme;
	int line = 0;
	Hash_table& table;
	void Function(Node& n);
	void Begin(Node& n);
	void End(Node& n);
	void FunctionName(Node& n);
	void Descriptions(Node& n);
	void Descriptions1(Node& n);
	void Operators(Node& n);
	void Operators1(Node& n);
	void Descr(Node& n);
	void VarList(Node& n);
	void VarList1(Node& n);
	void Type(Node& n);
	void Op(Node& n);
	void SimpleExpr(Node& n);
	void Expr(Node& n);
	void Expr1(Node& n);
	void Id(Node& n);
	void Const(Node& n);
public:
	void error(string str = "");
	void error(set<int>& err);
	Syntactic_analysis(Hash_table& table);
	void parse(Node& root, string type_lexeme, int line, string lexeme);
};
