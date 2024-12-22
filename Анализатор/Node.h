#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Node
{
private:
	vector<Node> children;
public:
	Node* root;
	string data, type;
	int line = 0;
	int size = 0;
	bool anons = 0;
	bool flag = 0;
	Node(string s, string type = "");
	void addSon(string s, string type = "", int line = 0);
	Node& operator[](int i);
	void print(int lvl = 0);
	bool iserror(set<int>& err);
	string postfix(int& it);
};
