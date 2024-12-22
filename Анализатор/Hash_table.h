#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "token.h"

class Hash_table
{
private:
	list_token* info;
	my_type size = 0;
	my_type count_elems = 0;

	my_type hash(string lexeme);
public:
	Hash_table() {}
	void resize(size_t size);
	void clear(Hash_table& table);
	token find(my_type hash);
	bool find_in_list(my_type index, my_type new_hash);
	void insert(string& type_new_lexeme, string& new_lexeme);
	void output(string path);
	~Hash_table();
};
