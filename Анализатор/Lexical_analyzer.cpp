#include "Lexical_analyzer.h"

//��������� ����� �� �����;
char buffer;
string Lexical_analyzer::next_lexeme(ifstream& file) {
	string word = "";
	char x = '/0';
	char x_op = '/0';
	if ((buffer == '=') || (buffer == '+') || (buffer == '-') || (buffer == '{') || (buffer == '}') ||
		(buffer == ';') || (buffer == '(') || (buffer == ')') || (buffer == ',')) {
		word += buffer;
		buffer = '/0';
		return word;
	}
	else {
		x = file.get();
		if (file.eof())
			return word;
	}
	//���������� �������� � ����� �� ������ ����� � ������;
	while ((!file.eof() && ((x == ' ') || (x == '\n') || (x == '\t'))))
	{
		if (x == '\n')
			line++;
		x = file.get();
	}
	if (!file.eof())
		word += x;
	if ((x == '=') || (x == '+') || (x == '-') || (x == '{') || (x == '}') ||
		(x == ';') || (x == '(') || (x == ')') || (x == ',')) {
		return word;
	}
	// ���������� �������� �� �����������
	while ((!file.eof() && (x != ' ') && (x != '\n') && (x != '\t')))
	{
		x = file.get();
		if ((x == '=') || (x == '+') || (x == '-') || (x == '{') || (x == '}') ||
			(x == ';') || (x == '(') || (x == ')') || (x == ',')) {
			buffer = x;
			break;
		}
		if (!file.eof() && (x != ' ') && (x != '\n') && (x != '\t'))
			word += x;
	}

	if (x == '\n')
		line++;

	return word;
}

//��������� � ��� �������;
void Lexical_analyzer::insert(Hash_table& table, int state, int st, string type_lexeme, string& lexeme, Node& root, Syntactic_analysis& synt) {
	if (state == st) {
		table.insert(type_lexeme, lexeme);
		if (state != -1) {
			synt.parse(root, type_lexeme, line, lexeme);
		}
		else synt.error("������� " + lexeme + " �� ����������");
	}
}

//	���������� � ������ ���� ��������� �������
void Lexical_analyzer::analyze(string path_input_file, Node& root) {
	ifstream file(path_input_file);

	dfa my;

	Hash_table table;
	table.resize(1000);

	Syntactic_analysis synt;

	string word;
	int state;
	string all6;
	while (!file.eof())
	{
		word.clear();
		word = next_lexeme(file);

		if (word.size() != 0) {
			all6 += " " + word;
			if (my.isAccept(word, state)) {

				// �������� ����� (int, double, return)
				insert(table, state, 16, "int", word, root, synt);
				insert(table, state, 25, "double", word, root, synt);
				insert(table, state, 26, "return", word, root, synt);

				// ��������� (=, +, -, itod, dtoi)
				insert(table, state, 7, "operator", word, root, synt);
				insert(table, state, 21, "operator", word, root, synt);

				// ����������� ({, }, (, ), ;, ,,)
				insert(table, state, 6, "delimiter", word, root, synt);

				// constant
				insert(table, state, 5, "int_num", word, root, synt);
				insert(table, state, 19, "double_num", word, root, synt);

				// ��������
				if (state >= 1 && state <= 4 || state >= 8 && state <= 12 || state == 14 || state == 15 ||
					state == 17 || state == 18 || state == 20 || state >= 22 && state <= 24)
					insert(table, state, state, "id_name", word, root, synt);
			}
			else {
				//������ ��������� �� ������ � ������ � ��������;
				insert(table, -1, -1, "Error", word, root, synt);
				//fout << word << "\n";
			}
		}
	}
	file.close();
	
	synt.parse(root, "", line, "#End");
	table.output("Hash_table.txt");
}
