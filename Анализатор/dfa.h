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
	int countStates; // ���������� ��������� ��������
	std::vector<char> alphabet; // ������� �������
	std::vector<int> finalStates; // ��������� ����������� ���������
	// transitFunction[i][j] = k ��������, ��� �� i-�� ��������� �� j-�� ������� �������� �������� ������� ��������� � ��������� k
	std::vector<std::vector<int>> transitFunction; // ������� ��������� 
	// ������� ��������� �������� �� �������� ��������� state � �������� ������� c
	int getState(int state, char c);
	// ������� ��� ���������, �� ������� ������� ��������� �� k-�� ����������� ������� � ��������� state
	std::set<int> inverse(int state, int k);
	// ������ ��������� ������� ��������������� �� ��������� ��������� (����� ��� ���������� ������������ ��������)
	std::vector<std::vector<int>> quotientSet();
public:
	dfa();
	dfa(int countStates, std::vector<char> alphabet, std::vector<int> finalStates, std::vector<std::vector<int>> transitFunction);
	dfa(const dfa& new_dfa);
	// ���������, ����������� �� ������ s ���������
	bool isAccept(std::string s, int& state);
	// ������ ������������� ��� � ����������� ������ ���������
	dfa minimize();
	// ������� ���� dfa.txt 
	void printf();
};
