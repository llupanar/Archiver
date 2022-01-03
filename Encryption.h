#pragma once

#include "Priority.h"
#include <vector>
#include <queue>
#include <bitset>
#include <SFML/Graphics.hpp>
#include <thread>
#include"gameInterface.h"
#include <windows.h>
#include "Errors.h"

using namespace std;

int yes_no();
using nodePtr_pQ = priority_queue <shared_ptr<Node>, vector<shared_ptr<Node>>, Priority>;
ifstream::pos_type get_size(const string& information);
void getFileInfo(string filename, vector<int>& freq);
void pushQueue(nodePtr_pQ& queue, vector<int> const freq);
void buildTree(nodePtr_pQ& queue);
void codeMaster(shared_ptr<Node>& node, string str, vector <string>& codes);
string make_codeString(const string& filename, vector <string>& codes);
void archiveMaker(const string& filename, vector<int>& freq, nodePtr_pQ& queue, const string& massage);
int encryptionFunc(sf::RenderWindow& window);