#include "Hash_table.h"

// Переопределяем размер хеш-таблицы
void Hash_table::resize(size_t new_size) {
	this->info = new list_token[new_size];
	this->size = new_size;
	for (int i = 0; i < size; i++)
		info[i].info = new token[0];
}

//Очищаем таблицу
void Hash_table::clear(Hash_table& table) {
	this->~Hash_table();
	table.count_elems = 0;
	table.size = 0;
}

//Поиск в таблице
token Hash_table::find(my_type hash) {
	my_type index = hash % this->size;
	
	for (int i = 0; i < this->info[index].size; i++) {
		if (hash == this->info[index][i].hash) {
			return this->info[index][i];
		}
	}
	//return;
}

// Нужно проверить find_table на возвращаемое значение
bool Hash_table::find_in_list(my_type index, my_type new_hash) {
	for (int i = 0; i < this->info[index].size; i++) {
		if (new_hash == this->info[index][i].hash) {
			return true;
		}
	}
	return false;
}

// Создание хэша
my_type Hash_table::hash(string lexeme) {
	int mod = 1e9;
	my_type* pow = new my_type[lexeme.size()];
	my_type* hash = new my_type[lexeme.size()];

	int simple_num = 127;
	pow[0] = 1;
	for (int i = 1; i < lexeme.size(); i++) {
		pow[i] = (pow[i - 1] * simple_num) % mod;
	}
	hash[0] = (int)(lexeme[0]);
	for (int i = 1; i < lexeme.size(); i++) {
		hash[i] = (pow[i] * (int)(lexeme[i]) + hash[i - 1]) % mod;
	}

	my_type res = hash[lexeme.size() - 1];
	delete[] pow;
	delete[] hash;
	return res;
}

// Вставка в твблицу
void Hash_table::insert(string& type_new_lexeme, string& new_lexeme) {
	my_type new_hash = hash(new_lexeme);
	my_type new_index = new_hash % this->size;
	token new_token(type_new_lexeme, new_lexeme, new_index, new_hash);

	// Если таблица полная
	if (this->count_elems == this->size) {
		printf("Insert Error: Hash Table is full\n");
		new_token.~token();
		return;
	}
	// Если в списке ноль элементов;
	if (this->info[new_index].size == 0) {
		// Добавляем новый элемент
		token* new_list = new token[info[new_index].size + 1];
		for (int i = 0; i < info[new_index].size; i++)
			new_list[i] = info[new_index][i];
		delete[] info[new_index].info;
		info[new_index].info = new_list;
		info[new_index][info[new_index].size] = new_token;
		info[new_index].size++;

		this->count_elems++;
	}
	else {
		if (find_in_list(new_index, new_hash) == false) {
			token* new_list = new token[info[new_index].size + 1];
			for (int i = 0; i < info[new_index].size; i++)
				new_list[i] = info[new_index][i];
			delete[] info[new_index].info;
			info[new_index].info = new_list;
			info[new_index][info[new_index].size] = new_token;
			info[new_index].size++;

			this->count_elems++;
		}
	}
}

string add_spaces(string str, int n = 10) {
	string S = "";
	int i = 0;
	for (; i < str.size(); i++)
		S += str[i];
	for (; i < n; i++)
		S += ' ';
	return S;
}

// Вывод таблицы в файл
void Hash_table::output(string path) {
	ofstream fout(path);
	if(fout.is_open())
		for (int i = 0; i < size; i++) {
			if (info[i].size > 0) {
				for (int j = 0; j < info[i].size; j++) {
					fout <<
						info[i][j].index << "\t" <<
						add_spaces(info[i][j].type_lexeme) << "\t" <<
						add_spaces(info[i][j].lexeme) << "\t" <<
						info[i][j].hash << '\n';
				}
			}
		}
	fout.close();
	return;
}

Hash_table::~Hash_table() {
	for (int i = 0; i < size; i++) {
		delete[] info[i].info;
	}
	delete[] info;
}
