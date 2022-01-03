#include "Encryption.h"

int yes_no()
{
	int choice = 0;
	cout << "[1] - yes\n[2] - no\n";
	choice = checkValue(1, 2);
	return choice;
}

ifstream::pos_type get_size(const string& information)
{
	ifstream ifs(information, ifstream::ate);
	if (!ifs) throw Errors(5);

	return ifs.tellg();
}

void getFileInfo(string filename, vector<int>& freq)
{
	int filesize = get_size(filename);
	if (filesize < 0) throw Errors(5);
	ifstream ifs(filename, ifstream::binary);
	system("cls");
	int i = 0;
	while (true) {
		char symbol;
		ifs.read(&symbol, 1);
		if (ifs.eof())break;
		freq[static_cast<unsigned char>(symbol)]++;
		int value = i * 100.0 / filesize;
		cout << "\r" << value + 1 << "%" << flush;
		i++;
	}
	system("cls");
	cout << "100%\n";
}
void pushQueue(nodePtr_pQ& queue, vector<int> const freq)
{
	for (int i = 0; i < freq.size(); ++i) {
		if (freq[i] != 0) {
			shared_ptr<Node> node = make_shared<Node>(i, freq[i]);
			queue.push(node);
		}
	}
}
void buildTree(nodePtr_pQ& queue)
{
	while (queue.size() > 1) {
		shared_ptr<Node> ptr = queue.top();
		queue.pop();
		shared_ptr<Node> ptr_ = queue.top();
		queue.pop();
		shared_ptr<Node> z = make_shared<Node>(0,ptr->get_frequency() + ptr_->get_frequency());
		z->left = ptr;
		z->right = ptr_;
		ptr->parent = z;
		ptr_->parent = z;
		queue.push(z);
	}
}

void codeMaster(shared_ptr<Node>& node, string str, vector<string>& codes)
{
	if (node->left != nullptr) {
		codeMaster(node->left, str + "0", codes);
	}
	if (node->right != nullptr)
		codeMaster(node->right, str + "1", codes);
	if (node->left == nullptr && node->right == nullptr) {
		node->set_code(str);
		codes[node->get_byte()] = str;
	}
}

string make_codeString(const string& filename, vector<string>& codes)
{

	string mass("");
	ifstream ifs(filename, ifstream::binary);
	while (true) {
		char ch;
		ifs.read(&ch, 1);
		if (ifs.eof())break;

		mass += codes[static_cast<uch_type>(ch)];
	}
	return mass;
}

void archiveMaker(const string& filename, vector<int>& freq, nodePtr_pQ& queue, const string& codeString)
{
	string archiveName = filename + ".ach";
	ofstream ofs(archiveName, ofstream::binary);
	uch_type count = count_if(freq.begin(), freq.end(), [](const int& value) {return(value != 0); });
	ofs.write(reinterpret_cast<char*>(&count), sizeof count);
	for (int i = 0; i < freq.size(); i++) {
		if (freq[i] != 0) {
			uch_type index = static_cast<uch_type> (i);
			ofs.write(reinterpret_cast<char*>(&index), sizeof index);
			ofs.write(reinterpret_cast<char*>(&freq[i]), sizeof freq[i]);
		}
	}

	int byte_count = codeString.size() / CHAR_BIT;
	uch_type modulo = codeString.size() % CHAR_BIT;
	ofs.write(reinterpret_cast<char*>(&byte_count), sizeof byte_count);
	ofs.write(reinterpret_cast<char*>(&modulo), sizeof modulo);

	int i = 0;
	for (; i < byte_count; i++) {
		bitset<CHAR_BIT> b(codeString.substr(i * CHAR_BIT, CHAR_BIT));
		uch_type value = static_cast<uch_type>(b.to_ulong());
		ofs.write(reinterpret_cast<char*>(&value), sizeof value);
	}

	if (modulo > 0) {
		bitset<CHAR_BIT> b(codeString.substr(i * CHAR_BIT, modulo));
		uch_type value = static_cast<uch_type>(b.to_ulong());
		ofs.write(reinterpret_cast<char*>(&value), sizeof value);
	}
	cout << "\nArchive created\n";
}

void creatingAlgoritm(string fileName) {

	vector<int> fileSymbol_frequency(0x100, 0);
	try {
		getFileInfo(fileName + ".txt", fileSymbol_frequency);
	}
	catch (Errors& problem)
	{
		problem.problems();
		Sleep(2000);
		system("cls");
		return;
	}
	catch (...) {
		cout << "UNCNOWN ERROR\n";
		Sleep(2000);
		system("cls");
		return;
	}
	nodePtr_pQ fileSymbol_frequencyQueue;
	pushQueue(fileSymbol_frequencyQueue, fileSymbol_frequency);
	buildTree(fileSymbol_frequencyQueue);
	shared_ptr<Node> root = fileSymbol_frequencyQueue.top();
	vector<string> codesArray(0x100, "");
	codeMaster(root, "", codesArray);
	string codeString = make_codeString(fileName + ".txt", codesArray);
	archiveMaker(fileName, fileSymbol_frequency, fileSymbol_frequencyQueue, codeString);
}

int encryptionFunc(sf::RenderWindow& window)
{
	int choice = 0;
	string fileName = "";
	cout << "Enter file name or way to this file (without .<type>)\n";
	fileName = fileNamecheck();
	system("cls");
	cout << "Creating an archive may take some time. Would you like to play a game?\n";
	choice = yes_no();
	system("cls");
	try {
		if (choice == 1) {
			std::thread arch_th(creatingAlgoritm, fileName);
			gameInterface(window);
			arch_th.join();
		}
		else {
			creatingAlgoritm(fileName);
			Sleep(3000);
		}
		system("cls");
		return 0;
	}
	catch (Errors& problem) {
		problem.problems();
		Sleep(3000);
		system("cls");
		return 0;
	}
}

