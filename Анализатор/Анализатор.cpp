#include <iostream>
#include "Lexical_analyzer.h"
#include "Syntactic_analysis.h"
#include "function.h"

using namespace std;

int main()
{
	//Convert_nfa_to_dfa();
	Lexical_analyzer analiz;
	Node root("Function");
	analiz.analyze("Test_code_1.txt", root);
	root.print(0);
}

/*
	dfa new_dfa;
	vector<string> str = { "int", "double","return","itod","dtoi","+","-","=","{","}","(",")",";",",","122352","1332.1235","aaaasdjicm","i","in","d","do","dou","doub","doubl","r","re","ret","retu","retur","it","ito","dt","dto" };
	set<int> s;
	int p;
	for (int i = 1; i < 2; i++)
		if (new_dfa.isAccept(str[i], p))
			s.insert(p);

	for (int i : s)
		cout << i << ' ';
*/