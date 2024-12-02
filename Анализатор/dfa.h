#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <fstream>

class dfa
{
private:
	int countStates; // количество состояний автомата
	std::vector<char> alphabet; // входной алфавит
	std::vector<int> finalStates; // множество допускающих состояний
	// transitFunction[i][j] = k означает, что из i-го состояния по j-му символу входного алфавита автомат переходит в состояние k
	std::vector<std::vector<int>> transitFunction; // функция переходов 
	// Находит состояние автомата по текущему состоянию state и входному символу c
	int getState(int state, char c);
	// Находит все состояния, из которых автомат переходит по k-му алфавитному символу в состояние state
	std::set<int> inverse(int state, int k);
	// Строит множество классов эквивалентности на множестве состояний (нужно для построения минимального автомата)
	std::vector<std::vector<int>> quotientSet();
public:
	dfa();
	dfa(int countStates, std::vector<char> alphabet, std::vector<int> finalStates, std::vector<std::vector<int>> transitFunction);
	dfa(const dfa& new_dfa);
	// Проверяет, допускается ли строка s автоматом
	bool isAccept(std::string s, int& state);
	// Строит эквивалентный ДКА с минимальным числом состояний
	dfa minimize();
	// Создает файл dfa.txt 
	void printf();
};
