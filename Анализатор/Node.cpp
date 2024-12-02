#include "Node.h"

Node::Node(string s)
{
	data = s;
	this->root = this;
}

void Node::addSon(string s)
{
	Node n(s);
	n.root = this;
	children.push_back(n);
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
	cout << data << endl;
	for (Node n : children)
		n.print(lvl + 1);
}