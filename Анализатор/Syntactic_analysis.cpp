#include "Syntactic_analysis.h"

void Syntactic_analysis::error(string str) {
	if (str.size() > 0)
		str += '\n';
	system("chcp 1251 > nul");
	ofstream out("error.txt");
	out << "ќшибка в строке " << line << "\n" << str;
	cout << "ќшибка в строке " << line << "\n" << str;
	out.close();
	exit(0);
}

void Syntactic_analysis::error(set<int>& err) {
	string str;
	system("chcp 1251 > nul");
	ofstream out("error.txt");
	for (int er : err) {
		out << "ќшибка типа данных в строке " << er << "\n";
		cout << "ќшибка типа данных в строке " << er << "\n";
	}
	out.close();
	exit(0);
}

Syntactic_analysis::Syntactic_analysis(Hash_table& table) : table(table) {
	ofstream out("error.txt");
	out << "";
	out.close();
}

void Syntactic_analysis::parse(Node& root, string type_lexeme, int line, string lexeme)
{
	this->lexeme = lexeme;
	this->line = line;
	this->type_lexeme = type_lexeme;
	if (root.flag == 0) {
		Function(root);
	}
	else if (lexeme != "#End") error();
}

void Syntactic_analysis::Function(Node& n)
{
	if (n.anons == 0) {
		n.addSon("Begin");
		n.addSon("Descriptions");
		n.addSon("Operators");
		n.addSon("End");
		n.anons = 1;
	}
	if (n[0].flag == 0) {
		Begin(n[0]);
	}
	else if (n[1].flag == 0) {
		Descriptions(n[1]);
		if (n[1].flag == 1 && type_lexeme == "id_name")
			Operators(n[2]);
	}
	else if (n[2].flag == 0 && n[1].flag == 1) {
		Operators(n[2]);
		if(n[2].flag == 1 && type_lexeme == "return")
			End(n[3]);
	}
	else if (n[3].flag == 0 && n[2].flag == 1) {
		End(n[3]);
		if (n[3].flag == 1) {
			n.flag = 1;
		}
	}
	else error();
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
	if (n[0].flag == 0) {
		Type(n[0]);
	}
	else if (n[1].flag == 0) {
		FunctionName(n[1]);
	}
	else if (n[2].flag == 0 && lexeme == "(") {
		n[2].flag = 1;
	}
	else if (n[3].flag == 0 && lexeme == ")" && n[2].flag == 1) {
		n[3].flag = 1;
	}
	else if (n[4].flag == 0 && lexeme == "{" && n[3].flag == 1) {
		n[4].flag = 1;
		n.flag = 1;
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
	if (n[0].flag == 0 && type_lexeme == "return") {
		n[0].flag = 1;
	}
	else if (n[1].flag == 0 && n[0].flag == 1) {
		if (!table.isfind(lexeme)) error("»дентификатор \"" + lexeme + "\" не определен");
		Id(n[1]);
	}
	else if (n[2].flag == 0 && lexeme == ";" && n[1].flag == 1) {
		n[2].flag = 1;
	}
	else if (n[3].flag == 0 && lexeme == "}" && n[2].flag == 1) {
		n[3].flag = 1;
		n.flag = 1;
	}
	else error();
}

void Syntactic_analysis::FunctionName(Node& n)
{
	if (n.anons == 0) {
		n.addSon("Id");
		n.anons = 1;
	}
	if (n[0].flag == 0) {
		Id(n[0]);
		if (n[0].flag == 1) {
			n.flag = 1;
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
	if (n[0].flag == 0) {
		 Descr(n[0]);
	}
	else if (n[1].flag == 0) {
		Descriptions1(n[1]);
		if (n[1].flag == 1) {
			n.flag = 1;
		}
	}
	else error();
}

void Syntactic_analysis::Descriptions1(Node& n)
{
	if (n.anons == 0 && type_lexeme == "id_name") {
		n.flag = 1;
		n.addSon("eps");
	}
	else {
		if (n.anons == 0) {
			n.addSon("Descr");
			n.addSon("Descriptions1");
			n.anons = 1;
		}
		if (n[0].flag == 0) {
			Descr(n[0]);
		}
		else if (n[1].flag == 0) {
			Descriptions1(n[1]);
			if (n[1].flag == 1) {
				n.flag = 1;
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
	if (n[0].flag == 0) {
		Op(n[0]);
	}
	else if (n[1].flag == 0) {
		Operators1(n[1]);
		if (n[1].flag == 1) {
			n.flag = 1;
		}
	}
	else error();
}

void Syntactic_analysis::Operators1(Node& n)
{
	if (n.anons == 0 && type_lexeme == "return") {
		n.flag = 1;
		n.addSon("eps");
	}
	else {
		if (n.anons == 0) {
			n.addSon("Op");
			n.addSon("Operators1");
			n.anons = 1;
		}
		if (n[0].flag == 0) {
			Op(n[0]);
		}
		else if (n[1].flag == 0) {
			Operators1(n[1]);
			if (n[1].flag == 1) {
				n.flag = 1;
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
	if (n[0].flag == 0) {
		Type(n[0]);
	}
	else if (n[1].flag == 0) {
		VarList(n[1]);
		if (n[1].flag == 1) {
			n.flag = 1;
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
	if (n[0].flag == 0) {
		if (table.isfind(lexeme)) error("ѕеременна€ \"" + lexeme + "\" уже была объ€влена");
		Id(n[0]);
	}
	else if (n[1].flag == 0) {
		VarList1(n[1]);
		if (n[1].flag == 1) {
			n.flag = 1;
		}
	}
	else error();
}

void Syntactic_analysis::VarList1(Node& n)
{
	if (n.anons == 0 && lexeme == ";") {
		n.addSon("eps");
		n.flag = 1;
	}
	else {
		if (n.anons == 0) {
			n.addSon(",");
			n.addSon("Id");
			n.addSon("VarList1");
			n.anons = 1;
		}
		if (n[0].flag == 0 && lexeme == ",") {
			n[0].flag = 1;
		}
		else if (n[0].flag == 1 && n[1].flag == 0) {
			if (table.isfind(lexeme)) error("ѕеременна€ \"" + lexeme + "\" уже была объ€влена");
			Id(n[1]);
		}
		else if (n[2].flag == 0 && n[1].flag == 1) {
			VarList1(n[2]);
			if (n[2].flag == 1) {
				n.flag = 1;
			}
		}
		else error();
	}
}

void Syntactic_analysis::Type(Node& n)
{
	if (type_lexeme == "int" || type_lexeme == "double") {
		n.addSon(lexeme, type_lexeme);
		n.flag = 1;
	}
	else error("ќжидалс€ тип данных вместо " + type_lexeme);
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
	if (n[0].flag == 0) {
		if (!table.isfind(lexeme)) error("»дентификатор \"" + lexeme + "\" не определен");
		Id(n[0]);
	}
	else if (n[1].flag == 0 && lexeme == "=") {
		n[1].flag = 1;
	}
	else if (n[2].flag == 0 && n[1].flag == 1) {
		Expr(n[2]);
		if (n[2].flag == 1) {
			n.flag = 1;
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
		else if (type_lexeme == "int_num" || type_lexeme == "double_num") {
			n.addSon("Const");
			n.anons = 1;
		}
		else if (type_lexeme == "id_name") {
			n.addSon("Id");
			n.anons = 1;
		}
		else error();
	}
	if (n[0].data == "itod") {
		if (n[0].flag == 0 && lexeme == "itod") {
			n[0].flag = 1;
		}
		else if (n[1].flag == 0 && lexeme == "(" && n[0].flag == 1) {
			n[1].flag = 1;
		}
		else if (n[2].flag == 0 && ((type_lexeme == "operator" && lexeme != "=") || lexeme == "(" || lexeme == ")" ||
			type_lexeme == "int_num" || type_lexeme == "double_num" || type_lexeme == "id_name") && n[1].flag == 1) {
			Expr(n[2]);
			if (n[2].flag == 1) {
				n[3].flag = 1;
				n.flag = 1;
			}
		}
		else error();
	}
	else if (n[0].data == "dtoi") {
		if (n[0].flag == 0 && lexeme == "dtoi") {
			n[0].flag = 1;
		}
		else if (n[1].flag == 0 && lexeme == "(" && n[0].flag == 1) {
			n[1].flag = 1;
		}
		else if (n[2].flag == 0 && ((type_lexeme == "operator" && lexeme != "=") || lexeme == "(" || lexeme == ")" ||
			type_lexeme == "int_num" || type_lexeme == "double_num" || type_lexeme == "id_name") && n[1].flag == 1) {
			Expr(n[2]);
			if (n[2].flag == 1) {
				n[3].flag = 1;
				n.flag = 1;
			}
		}
		else error();
	}
	else if (n[0].data == "(") {
		if (n[0].flag == 0 && lexeme == "(") {
			n[0].flag = 1;
		}
		else if (n[1].flag == 0 && ((type_lexeme == "operator" && lexeme != "=") || lexeme == "(" || lexeme == ")" ||
			type_lexeme == "int_num" || type_lexeme == "double_num" || type_lexeme == "id_name") && n[0].flag == 1) {
			Expr(n[1]);
			if(n[1].flag == 1){
				n[2].flag = 1;
				n.flag = 1;
			}
		}
		else error();
	}
	else if (n[0].data == "Const") {
		Const(n[0]);
		if (n[0].flag == 1) {
			n.flag = 1;
		}
	}
	else if (n[0].data == "Id") {
		if (!table.isfind(lexeme)) error("»дентификатор \"" + lexeme + "\" не определен");
		Id(n[0]);
		if (n[0].flag == 1) {
			n.flag = 1;
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
	if (n[0].flag == 0) {
		SimpleExpr(n[0]);
	}
	else if (n[1].flag == 0) {
		Expr1(n[1]);
		if (n[1].flag == 1) {
			n.flag = 1;
		}
	}
	else error();
}

void Syntactic_analysis::Expr1(Node& n)
{
	if (n.anons == 0 && (lexeme == ")" || lexeme == ";")) {
		n.addSon("eps");
		n.anons = 1;
		n.flag = 1;
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
			n.anons = 1;
		}
		if (n.size == 3 && n[0].flag == 0) {
			n[0].flag = 1;
		}
		else if (n.size == 3 && n[1].flag == 0 && n[0].flag == 1) {
			SimpleExpr(n[1]);
		}
		else if (n.size == 3 && n[2].flag == 0 && n[1].flag == 1) {
			Expr1(n[2]);
			if (n[2].flag == 1) {
				n.flag = 1;
			}
		}
		else error();
	}
}

void Syntactic_analysis::Id(Node& n)
{
	if (type_lexeme == "id_name") {
		token t = table.find(lexeme);
		n.addSon(lexeme, t.type, line);
		n.flag = 1;
	}
	else error("ќжидалось им€ переменной вместо " + type_lexeme);
}

void Syntactic_analysis::Const(Node& n)
{
	if (type_lexeme == "int_num" || type_lexeme == "double_num") {
		string type = type_lexeme == "int_num" ? "int" : "double";
		n.addSon(lexeme, type, line);
		n.flag = 1;
	}
	else error("ќжидалось число вместо " + type_lexeme);
}
