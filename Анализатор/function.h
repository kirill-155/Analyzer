#pragma once
#include <set>
#include <fstream>
#include "nfa.h"
#include "dfa.h"


void Convert_nfa_to_dfa() {
	int countStates; // количество состояний автомата
	std::vector<char> alphabet; // входной алфавит
	std::vector<int> finalStates; // множество допускающих состояний
	std::vector<std::vector<std::vector<int>>> transitFunction; // функция переходов
	std::ifstream in("Функции переходов nfa.txt");
	if (in.is_open()) {
		countStates = 28;
		for (char c = 'a'; c <= 'z'; c++) {
			alphabet.push_back(c);
		}
		for (char c = 'A'; c <= 'Z'; c++) {
			alphabet.push_back(c);
		}
		for (char c = '0'; c <= '9'; c++) {
			alphabet.push_back(c);
		}
		alphabet.push_back('{');
		alphabet.push_back('}');
		alphabet.push_back('(');
		alphabet.push_back(')');
		alphabet.push_back(';');
		alphabet.push_back(',');
		alphabet.push_back('.');
		alphabet.push_back('=');
		alphabet.push_back('+');
		alphabet.push_back('-');

		finalStates.push_back(3);
		finalStates.push_back(14);
		finalStates.push_back(18);
		finalStates.push_back(22);
		finalStates.push_back(24);
		finalStates.push_back(25);
		finalStates.push_back(26);
		finalStates.push_back(27);

		transitFunction.resize(countStates);
		for (int i = 0; i < countStates; i++)
			transitFunction[i].resize(alphabet.size());
		int i, j, q;
		char c;
		while (!in.eof())
		{
			in >> i >> c >> q;
			for (j = 0; j < alphabet.size(); j++)
				if (c == alphabet[j])
					break;
			transitFunction[i][j].push_back(q);
		}

		for (int i = 0; i < transitFunction.size(); i++)
			for (j = 0; j < transitFunction[i].size(); j++)
				if (transitFunction[i][j].size() == 0)
					transitFunction[i][j].push_back(-1);

		nfa new_nfa(countStates, alphabet, finalStates, transitFunction);
		dfa new_dfa = new_nfa.createDFA();
		new_dfa.minimize();
		new_dfa.printf();
	}
	in.close();
}