#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Node
{
private:
	vector<Node> children;
public:
	Node* root;
	string data;
	int size = 0;
	bool anons = 0;
	bool flage = 0;
	Node(string s);
	void addSon(string s);
	Node& operator[](int i);
	void print(int lvl);
};
