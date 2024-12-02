#include "Syntactic_analysis.h"

void Syntactic_analysis::error(string str = "") {
	ofstream out("error.txt");
	out << "ќшибка в строке " << line;
	out.close();
	exit(0);
}

Syntactic_analysis::Syntactic_analysis() {
}

void Syntactic_analysis::parse(Node& root, string lex, int line, string str)
{
	param = str;
	this->line = line;
	lexeme = lex;
	if (root.flage == 0) {
		Function(root);
	}
	else if (str != "#End") error();
}

void Syntactic_analysis::Function(Node& n)
{
	bool f = 1;
	if (n.anons == 0) {
		n.addSon("Begin");
		n.addSon("Descriptions");
		n.addSon("Operators");
		n.addSon("End");
		n.anons = 1;
	}
	if (n[0].flage == 0) {
		Begin(n[0]);
		f = 0;
	}
	else if (n[1].flage == 0) {
		Descriptions(n[1]);
		f = 0;
	}
	if (n[2].flage == 0 && n[1].flage == 1) {
		Operators(n[2]);
		f = 0;
	}
	if (n[3].flage == 0 && n[2].flage == 1) {
		End(n[3]);
		if (n[3].flage == 1) {
			n.flage = 1;
		}
		f = 0;
	}
	if(f) error();
}

void Syntactic_analysis::Begin(Node& n)
{
	if (n.anons == 0) {
		n.addSon("Type");
		n.addSon("FunctionName");
		n.addSon("(");
		n.addSon(")");
		n.addSon("{");
		n.anons = 1;
	}
	if (n[0].flage == 0) {
		Type(n[0]);
	}
	else if (n[1].flage == 0) {
		FunctionName(n[1]);
	}
	else if (n[2].flage == 0 && lexeme == "(") {
		n[2].flage = 1;
	}
	else if (n[3].flage == 0 && lexeme == ")" && n[2].flage == 1) {
		n[3].flage = 1;
	}
	else if (n[4].flage == 0 && lexeme == "{" && n[3].flage == 1) {
		n[4].flage = 1;
		n.flage = 1;
	}
	else error();
}

void Syntactic_analysis::End(Node& n)
{
	if (n.anons == 0) {
		n.addSon("return");
		n.addSon("Id");
		n.addSon(";");
		n.addSon("}");
		n.anons = 1;
	}
	if (n[0].flage == 0 && lexeme == "return") {
		n[0].flage = 1;
	}
	else if (n[1].flage == 0 && n[0].flage == 1) {
		Id(n[1]);
	}
	else if (n[2].flage == 0 && lexeme == ";" && n[1].flage == 1) {
		n[2].flage = 1;
	}
	else if (n[3].flage == 0 && lexeme == "}" && n[2].flage == 1) {
		n[3].flage = 1;
		n.flage = 1;
	}
	else error();
}

void Syntactic_analysis::FunctionName(Node& n)
{
	if (n.anons == 0) {
		n.addSon("Id");
		n.anons = 1;
	}
	if (n[0].flage == 0) {
		Id(n[0]);
		if (n[0].flage == 1) {
			n.flage = 1;
		}
	}
	else error();
}

void Syntactic_analysis::Descriptions(Node& n)
{
	if (n.anons == 0) {
		n.addSon("Descr");
		n.addSon("Descriptions1");
		n.anons = 1;
	}
	if (n[0].flage == 0) {
		 Descr(n[0]);
	}
	else if (n[1].flage == 0) {
		Descriptions1(n[1]);
		if (n[1].flage == 1) {
			n.flage = 1;
		}
	}
	else error();
}

void Syntactic_analysis::Descriptions1(Node& n)
{
	if (n.anons == 0 && lexeme == "id_name") {
		n.flage = 1;
		n.addSon("eps");
	}
	else {
		if (n.anons == 0) {
			n.addSon("Descr");
			n.addSon("Descriptions1");
			n.anons = 1;
		}
		if (n[0].flage == 0) {
			Descr(n[0]);
		}
		else if (n[1].flage == 0) {
			Descriptions1(n[1]);
			if (n[1].flage == 1) {
				n.flage = 1;
			}
		}
		else error();
	}
}

void Syntactic_analysis::Operators(Node& n)
{
	if (n.anons == 0) {
		n.addSon("Op");
		n.addSon("Operators1");
		n.anons = 1;
	}
	if (n[0].flage == 0) {
		Op(n[0]);
	}
	else if (n[1].flage == 0) {
		Operators1(n[1]);
		if (n[1].flage == 1) {
			n.flage = 1;
		}
	}
	else error();
}

void Syntactic_analysis::Operators1(Node& n)
{
	if (n.anons == 0 && lexeme == "return") {
		n.flage = 1;
		n.addSon("eps");
	}
	else {
		if (n.anons == 0) {
			n.addSon("Op");
			n.addSon("Operators1");
			n.anons = 1;
		}
		if (n[0].flage == 0) {
			Op(n[0]);
		}
		else if (n[1].flage == 0) {
			Operators1(n[1]);
			if (n[1].flage == 1) {
				n.flage = 1;
			}
		}
		else error();
	}
}

void Syntactic_analysis::Descr(Node& n)
{
	if (n.anons == 0) {
		n.addSon("Type");
		n.addSon("VarList");
		n.addSon(";");
		n.anons = 1;
	}
	if (n[0].flage == 0) {
		Type(n[0]);
	}
	else if (n[1].flage == 0) {
		VarList(n[1]);
		if (n[1].flage == 1) {
			n.flage = 1;
		}
	}
	else error();
}

void Syntactic_analysis::VarList(Node& n)
{
	if (n.anons == 0) {
		n.addSon("Id");
		n.addSon("VarList1");
		n.anons = 1;
	}
	if (n[0].flage == 0) {
		Id(n[0]);
	}
	else if (n[1].flage == 0) {
		VarList1(n[1]);
		if (n[1].flage == 1) {
			n.flage = 1;
		}
	}
	else error();
}

void Syntactic_analysis::VarList1(Node& n)
{
	if (n.anons == 0 && lexeme == ";") {
		n.addSon("eps");
		n.flage = 1;
	}
	else {
		if (n.anons == 0) {
			n.addSon(",");
			n.addSon("Id");
			n.addSon("VarList1");
			n.anons = 1;
		}
		if (n[0].flage == 0 && lexeme == ",") {
			n[0].flage = 1;
		}
		else if (n[0].flage == 1 && n[1].flage == 0) {
			Id(n[1]);
		}
		else if (n[2].flage == 0 && n[1].flage == 1) {
			VarList1(n[2]);
			if (n[2].flage == 1) {
				n.flage = 1;
			}
		}
		else error();
	}
}

void Syntactic_analysis::Type(Node& n)
{
	if (lexeme == "int") {
		n.addSon("int");
		n.flage = 1;
	}
	else if (lexeme == "double") {
		n.addSon("double");
		n.flage = 1;
	}
	else error("ќжидалс€ тип данных вместо " + lexeme);
}

void Syntactic_analysis::Op(Node& n)
{
	if (n.anons == 0) {
		n.addSon("Id");
		n.addSon("=");
		n.addSon("Expr");
		n.addSon(";");
		n.anons = 1;
	}
	if (n[0].flage == 0) {
		Id(n[0]);
	}
	else if (n[1].flage == 0 && lexeme == "=") {
		n[1].flage = 1;
	}
	else if (n[2].flage == 0 && n[1].flage == 1) {
		Expr(n[2]);
		if (n[2].flage == 1) {
			n.flage = 1;
		}
	}
	else error();
}

void Syntactic_analysis::SimpleExpr(Node& n)
{
	if (n.anons == 0) {
		if (lexeme == "itod") {
			n.addSon("itod");
			n.addSon("(");
			n.addSon("Expr");
			n.addSon(")");
			n.anons = 1;
		}
		else if (lexeme == "dtoi") {
			n.addSon("dtoi");
			n.addSon("(");
			n.addSon("Expr");
			n.addSon(")");
			n.anons = 1;
		}
		else if (lexeme == "(") {
			n.addSon("(");
			n.addSon("Expr");
			n.addSon(")");
			n.anons = 1;
		}
		else if (lexeme == "int_num" || lexeme == "double_num") {
			n.addSon("Const");
			n.anons = 1;
		}
		else if (lexeme == "id_name") {
			n.addSon("Id");
			n.anons = 1;
		}
		else error();
	}
	if (n[0].data == "itod") {
		if (n[0].flage == 0 && lexeme == "itod") {
			n[0].flage = 1;
		}
		else if (n[1].flage == 0 && lexeme == "(" && n[0].flage == 1) {
			n[1].flage = 1;
		}
		else if (n[2].flage == 0 && (lexeme == "+" || lexeme == "-" || lexeme == "itod" || lexeme == "dtoi" || lexeme == "(" || lexeme == "int_num" || lexeme == "double_num" || lexeme == "id_name") && n[1].flage == 1) {
			Expr(n[2]);
		}
		else if (n[3].flage == 0 && lexeme == ")") {
			Expr(n[2]);
			n[3].flage = 1;
			n.flage = 1;
		}
		else error();
	}
	else if (n[0].data == "dtoi") {
		if (n[0].flage == 0 && lexeme == "dtoi") {
			n[0].flage = 1;
		}
		else if (n[1].flage == 0 && lexeme == "(" && n[0].flage == 1) {
			n[1].flage = 1;
		}
		else if (n[2].flage == 0 && (lexeme == "+" || lexeme == "-" || lexeme == "itod" || lexeme == "dtoi" || lexeme == "(" || lexeme == "int_num" || lexeme == "double_num" || lexeme == "id_name") && n[1].flage == 1) {
			Expr(n[2]);
		}
		else if (n[3].flage == 0 && lexeme == ")") {
			Expr(n[2]); 
			n[3].flage = 1;
			n.flage = 1;
		}
		else error();
	}
	else if (n[0].data == "(") {
		if (n[0].flage == 0 && lexeme == "(") {
			n[0].flage = 1;
		}
		else if (n[1].flage == 0 && (lexeme == "+" || lexeme == "-" || lexeme == "itod" || lexeme == "dtoi" || lexeme == "(" || lexeme == "int_num" || lexeme == "double_num" || lexeme == "id_name") && n[0].flage == 1) {
			Expr(n[1]);
		}
		else if (n[2].flage == 0 && lexeme == ")") {
			Expr(n[1]);
			n[2].flage = 1;
			n.flage = 1;
		}
		else error();
	}
	else if (n[0].data == "Const") {
		Const(n[0]);
		if (n[0].flage == 1) {
			n.flage = 1;
		}
	}
	else if (n[0].data == "Id") {
		Id(n[0]);
		if (n[0].flage == 1) {
			n.flage = 1;
		}
	}
	else error();
}

void Syntactic_analysis::Expr(Node& n)
{
	if (n.anons == 0) {
		n.addSon("SimpleExpr");
		n.addSon("Expr1");
		n.anons = 1;
	}
	if (n[0].flage == 0) {
		SimpleExpr(n[0]);
	}
	else if (n[1].flage == 0) {
		Expr1(n[1]);
		if (n[1].flage == 1) {
			n.flage = 1;
		}
	}
	else error();
}

void Syntactic_analysis::Expr1(Node& n)
{
	if (lexeme == "return")
		error();
	if (n.anons == 0 && (lexeme == ")" || lexeme == ";")) {
		n.addSon("eps");
		n.anons = 1;
		n.flage = 1;
	}
	else {
		if (n.anons == 0) {
			if (lexeme == "+") {
				n.addSon("+");
				n.addSon("SimpleExpr");
				n.addSon("Expr1");
			}
			else if (lexeme == "-") {
				n.addSon("-");
				n.addSon("SimpleExpr");
				n.addSon("Expr1");
			}
			else
				n.anons = 1;
		}
		if (n.size > 0 && n[0].flage == 0) {
			n[0].flage = 1;
		}
		else if (n.size > 0 && n[1].flage == 0 && n[0].flage == 1) {
			SimpleExpr(n[1]);
		}
		else if (n.size > 0 && n[2].flage == 0 && n[1].flage == 1) {
			Expr1(n[2]);
			if (n[2].flage == 1) {
				n.flage = 1;
			}
		}
		else error();
	}
}

void Syntactic_analysis::Id(Node& n)
{
	if (lexeme == "id_name") {
		n.addSon(param);
		n.flage = 1;
	}
	else error("ќжидалось им€ переменной вместо " + lexeme);
}

void Syntactic_analysis::Const(Node& n)
{
	if (lexeme == "int_num") {
		n.addSon(param);
		n.flage = 1;
	}
	else if (lexeme == "double_num") {
		n.addSon(param);
		n.flage = 1;
	}
	else error("ќжидалось число вместо " + lexeme);
}
