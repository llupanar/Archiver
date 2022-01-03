#pragma once
#include "Encryption.h"

using namespace std;

void unarchiveMaker(string& filename, vector<int>& fileSymbol_frequency, string& mass);
void make_char(shared_ptr<Node>& root, string& massage, string& text);
void make_file(string& text, string fileName);
int DencryptionFunc();