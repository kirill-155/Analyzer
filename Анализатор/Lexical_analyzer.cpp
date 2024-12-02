#include "Lexical_analyzer.h"

//ñëåäóşùåå ñëîâî èç ôàéëà;
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
	//ñ÷èòûâàíèå ïğîáåëîâ â ôàéëå äî ïåğâîé áóêâû â ñòğîêå;
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
	// Ñ÷èòûâàíèå ñèìâîëîâ äî ğàçäåëèòåëÿ
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

int Lexical_analyzer::get_last_state_from_path(string& path) {
	int i = path.size() - 1;
	while (path[i] == ' ') {
		i--;
	}

	string str_for_state = "";
	while (path[i] != ' ') {
		str_for_state += path[i];

		i--;
	}

	reverse(str_for_state.begin(), str_for_state.end());

	return stoi(str_for_state);
}

//äîáàâëÿåì â õıø òàáëèöó;
void Lexical_analyzer::insert(Hash_table& table, int state, int st, string type_lexeme, string lexeme, Node& root, Syntactic_analysis& synt) {
	if (state == st) {
		table.insert(type_lexeme, lexeme);
		if (state != -1) {
			if (type_lexeme == "int     ")
				synt.parse(root, "int", line, lexeme);
			else if (type_lexeme == "double  ")
				synt.parse(root, "double", line, lexeme);
			else if (type_lexeme == "return  ")
				synt.parse(root, "return", line, lexeme);
			else if (type_lexeme == "operator  ")
				synt.parse(root, lexeme, line, lexeme);
			else if (type_lexeme == "delimiter ")
				synt.parse(root, lexeme, line, lexeme);
			else if (type_lexeme == "int_num   ")
				synt.parse(root, "int_num", line, lexeme);
			else if (type_lexeme == "double_num")
				synt.parse(root, "double_num", line, lexeme);
			else if (type_lexeme == "id_name   ")
				synt.parse(root, "id_name", line, lexeme);
		}
	}
}

//	Îïğåäåëÿåì ê êàêîìó òèïó îòíîñèòñÿ ëåêñåìà
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

				// Êëş÷åâûå ñëîâà (int, double, return)
				insert(table, state, 16, "int     ", word, root, synt);
				insert(table, state, 25, "double  ", word, root, synt);
				insert(table, state, 26, "return  ", word, root, synt);

				// Îïåğàòîğû (+, -, =, itod, dtoi)
				insert(table, state, 7, "operator  ", word, root, synt);
				insert(table, state, 21, "operator  ", word, root, synt);

				// Ğàçäåëèòåëè ({, }, (, ), ;, ,,)
				insert(table, state, 6, "delimiter ", word, root, synt);

				// constant
				insert(table, state, 5, "int_num   ", word, root, synt);
				insert(table, state, 19, "double_num", word, root, synt);

				// Íàçâàíèÿ
				if (state >= 1 && state <= 4 || state >= 8 && state <= 12 || state == 14 || state == 15 ||
					state == 17 || state == 18 || state == 20 || state >= 22 && state <= 24)
					insert(table, state, state, "id_name   ", word, root, synt);
			}
			else {
				//âûäàåì ñîîáùåíèå îá îøèáêå ñ ôàéëîì ñ îøèáêàìè;
				insert(table, -1, -1, "Error     ", word, root, synt);
				//fout << word << "\n";
			}
		}
	}
	synt.parse(root, "double_num", line, "#End");
	file.close();
	table.output("output.txt");
	
}
