#pragma once

using namespace std;
typedef unsigned long long my_type;

struct token {
	string type_lexeme, lexeme, type = "";

	my_type index = 0, hash = 0;
	int size_lexeme = 0;

	token() = default;
	token(string& new_type, string& new_lexeme, my_type& new_index, my_type& new_hash, string& type)
		: type_lexeme(new_type), lexeme(new_lexeme), index(new_index), hash(new_hash), type(type), size_lexeme(lexeme.size()) {}

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
