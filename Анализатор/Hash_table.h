#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "token.h"

class Hash_table
{
private:
	list_token* info = new list_token[0];
	my_type size = 0;
	my_type count_elems = 0;

	my_type hash(string lexeme);
	bool find_table(my_type index, my_type new_hash);
public:
	Hash_table() {}
	void resize(size_t size);
	void clear(Hash_table& table);
	token find(string lexeme);
	bool isfind(string lexeme);
	void insert(string& type_new_lexeme, string& new_lexeme, string& type);
	void output(string path);
	~Hash_table();
};
