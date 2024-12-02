#pragma once

using namespace std;
typedef unsigned long long my_type;

struct token {
	string type_lexeme;
	string lexeme;

	my_type index;
	my_type hash;
	int size_lexeme;

	token() {};
	token(string new_type, string new_lexeme, my_type new_index, my_type new_hash)
		: type_lexeme(new_type), lexeme(new_lexeme), index(new_index), hash(new_hash) {}

	~token() {
		lexeme.clear();
		lexeme.shrink_to_fit();
		type_lexeme.clear();
		type_lexeme.shrink_to_fit();
	}
};

struct list_token {
	token* info;
	my_type size = 0;

	token& operator [] (size_t i) {
		return info[i];
	}

};
