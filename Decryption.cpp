#include "Decryption.h"

void unarchiveMaker(string& filename, vector<int>& fileSymbol_frequency, string& codeString)
{
	ifstream ifs(filename + ".ach", ifstream::binary);
	if (!ifs) throw Errors(5);
	if (ifs.peek() == EOF) throw Errors(3);
	uch_type count = 0;
	ifs.read(reinterpret_cast<char*>(&count), sizeof count);
	int i = 0;
	while (i < count) {
		uch_type symbol;
		ifs.read(reinterpret_cast<char*>(&symbol), sizeof symbol);
		int freq = 0;
		ifs.read(reinterpret_cast<char*>(&freq), sizeof freq);
		fileSymbol_frequency[symbol] = freq;
		i++;
	}

	int byte_count = 0;
	uch_type modulo = 0;
	ifs.read(reinterpret_cast<char*>(&byte_count), sizeof byte_count);
	ifs.read(reinterpret_cast<char*>(&modulo), sizeof modulo);
	i = 0;
	for (; i < byte_count; i++) {
		uch_type byte;
		ifs.read(reinterpret_cast<char*>(&byte), sizeof byte);
		bitset<CHAR_BIT>b(byte);
		codeString += b.to_string();
	}
	if (modulo > 0) {
		uch_type byte;
		ifs.read(reinterpret_cast<char*>(&byte), sizeof byte);
		bitset<CHAR_BIT>b(byte);
		codeString += b.to_string().substr(CHAR_BIT - modulo, CHAR_BIT);
	}

}

void make_char(shared_ptr<Node>& root, string& massage, string& text)
{
	shared_ptr<Node> node = root;
	for (size_t i = 0; i < massage.size(); i++) {
		char t_symbol = massage[i];
		if (t_symbol == '0') {
			if (node->left != nullptr) {
				node = node->left;
			}
			if (node->is_leaf()) {
				text += node->get_byte();
				node = root;
			}
		}
		else {
			if (t_symbol == '1') {
				if (node->right != nullptr) {
					node = node->right;
				}
				if (node->is_leaf()) {
					text += node->get_byte();
					node = root;
				}
			}
		}
	}
}

void make_file(string& text, string fileName)
{
	string filename = fileName + "_.txt";
	ofstream ofs(filename);
	ofs << text;
}

int DencryptionFunc()
{
	vector<int> fileSymbol_frequency(0x100, 0);
	string codeString = "";
	string fileName = "";
	cout << "Enter archive name (without .<type>)\n";
	fileName = fileNamecheck();
	system("cls");
	cout << "Wait...\n";
	nodePtr_pQ fileSymbol_frequencyQueue;
	try {
		unarchiveMaker(fileName, fileSymbol_frequency, codeString);
	}
	catch (Errors& problem)
	{
		problem.problems();
		Sleep(2000);
		system("cls");
		return 0;
	}
	catch (...) {
		cout << "UNCNOWN ERROR\n";
		Sleep(2000);
		system("cls");
		return 0;
	}
	pushQueue(fileSymbol_frequencyQueue, fileSymbol_frequency);
	buildTree(fileSymbol_frequencyQueue);
	shared_ptr<Node> root = fileSymbol_frequencyQueue.top();
	string decr_archiveText = "";
	make_char(root, codeString, decr_archiveText);
	make_file(decr_archiveText, fileName);
	cout << "!DONE!";
	Sleep(3000);
	system("cls");
	return 0;
}
