#pragma once
#include <vector>
#include "Hash_table.h"
#include "dfa.h"
#include "Syntactic_analysis.h"

class Lexical_analyzer
{
private:
	int line = 1;

public:
	Lexical_analyzer() {}

	string next_lexeme(ifstream& file);

	void insert(Hash_table& table, int state, int st, string type_lexeme, string& lexeme, Node& root, Syntactic_analysis& synt);

	void analyze(string path_input_file, Node& root);

	~Lexical_analyzer() {}
};

