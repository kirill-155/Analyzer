#include "Node.h"

Node::Node(string s, string type) : type(type)
{
	data = s;
	this->root = this;
}

void Node::addSon(string s, string type, int line)
{
	Node n(s, type);
	n.root = this;
	children.push_back(n);
	children[size].line = line;
	size++;
}

Node& Node::operator[](int i)
{
	return children[i];
}

void Node::print(int lvl)
{
	for (int i = 0; i < lvl; ++i)
		cout << "  ";
	cout << data << " " << type << endl;
	for (Node n : children)
		n.print(lvl + 1);
}

bool Node::iserror(set<int>& err) {
	if (size == 0)// если дочерних элементов нет
		return 0;

	for (int i = 0; i < size; i++)// сначала провести проверку в дочерних узлах
		children[i].iserror(err);// если в дочернем узле ошибка

	string tp = "";
	int ln = 0;
	for (int i = size - 1; i >= 0; i--)// запись первого встретившегося типа данных
		if (children[i].type != tp){
			tp = children[i].type;
			ln = children[i].line;
			break;
		}

	for (Node n : children)
		if (n.type != "" && n.type != tp && n.data != "Operators1" && n.data != "Op" && n.data != "Descriptions1" && n.data != "Descr") {// если тип данных в дочерних узлах разный
			err.insert(ln);
			return 1;
		}

	line = ln;
	if (children[0].data == "dtoi") {
		if(tp != "double") {// если тип данных разный
			err.insert(ln);
			return 1;
		}
		this->type = "int";
	}
	else if (children[0].data == "itod") {
		if (tp != "int") {// если тип данных разный
			err.insert(ln);
			return 1;
		}
		this->type = "double";
	}
	else this->type = tp;// копировать тип данных из дочернего узла
	if (data == "Operators" || data == "Descriptions")
		this->type = "";
	return 0;
}

string Node::postfix(int& it) {
	if (size == 0)// если дочерних элементов нет
		return data + " ";

	string str = "", post = "";
	for (int i = 0; i < size; i++) {
		if (children[i].data != "(" && children[i].data != ")" && children[i].data != "}" && children[i].data != "eps") {
			if (children[i].data == ",")
				it++;
			else if (children[i].data == "{" || children[i].data == ";")
				post += '\n';
			else if (children[i].data == "=" || children[i].data == "-" || children[i].data == "+")
				post += children[i].data + " ";
			else
				str += children[i].postfix(it);

			if (children[i].data == "FunctionName"){
				post += "functionBegin";
			}
			else if (children[i].data == "itod" || children[i].data == "dtoi")
				post += "CALL ";
			else if (children[i].data == "return")
				post += "functionEnd";
			else if (children[i].data == "VarList"){
				post += to_string(2+it) + " DECL";
				it = 0;
			}
		}
	}
	str += post;
	return str;
}
