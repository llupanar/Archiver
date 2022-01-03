#pragma once
#include <iostream>
#include <string>
#include <fstream>


using namespace std;

class Errors {
private:
    int code{ 0 };
public:
    Errors() = default;
    Errors(int error);
    void problems();
};
int checkValue(int leftBoard, int rightBoard);
string fileNamecheck();
bool correctSymbols_fileName(string str);
bool typeCheck(string str);

