#include "Errors.h"

Errors::Errors(int error)
{
    this->code = error;
}

void Errors::problems()
{

    switch (code) {
    case 1:
        cout << "INCORRECT TYPE\n";
        break;
    case 2:
        cout << "THE LIMIT OF ACCEPTABLE VALUES HAS BEEN EXCEEDED\n";
        break;
    case 3:
        cout << "FILE EMPTY\n";
        break;
    case 4:
        cout << "INCORRECT FILE NAME. ENTER THE NAME WITHOUT .<TYPE>\n";
        break;
    case 5:
        cout << "FILE DOESNT EXIST\n";
        break;
    case 6:
        cout << "FILE WITH THIS NAME CANT EXIST\n";
        break;
    }
}

int checkValue(int leftBoard, int rightBoard) {
    int value;
    do
    {
        try
        {
            cin >> value;
            if (cin.fail()) throw Errors(1);
            if ((rightBoard != 0) && (value > rightBoard || value < leftBoard)) throw Errors(2);
        }
        catch (Errors& problem)
        {
            cin.clear();
            cin.ignore(3256, '\n');
            problem.problems();
            value = 0;
        }
        catch (...) {
            cout << "UNCNOWN ERROR\n";
            abort();
            exit(1);
        }
    } while (value == 0);

    return value;
}


string fileNamecheck() {

    string fileName;
    int flag = 0;
    do
    {
        try
        {
            rewind(stdin);
            getline(cin, fileName);
            if (!correctSymbols_fileName(fileName))throw Errors(6);
            if (!typeCheck(fileName))throw Errors(4);
            return fileName;
        }
        catch (Errors& problem)
        {
            problem.problems();

        }
        catch (...) {
            cout << "UNCNOWN ERROR\n";
            exit(1);
        }

    } while (flag == 0);
    return "";
}
bool correctSymbols_fileName(string str) {
    int length = str.length();
    int i = 0;
    while (length--) {
        if (/*str[i] < 32 ||*/ str[i] == '*' || str[i] == '#' || str[i] == '?'
            || str[i] == '!' || str[i] == '<' || str[i] == '>' || str[i] == '{'
            || str[i] == '}' || str[i] == '@' || str[i] == '&' || str[i] == '%'
            || str[i] == '$' || str[i] == '"' || str[i] == ':' || str[i] == '='
            || str[i] == '|' || str[i] == '+' || str[i] == '`') {
            return false;
        }
        i++;
    }
    if (length == 1 && str[0] == ' ') return false;
    return true;
}
bool typeCheck(string str) {

    int length = str.length();
    int i = 0;
    string typeStr = "";
    if (str[length - 4] == '.') {
        typeStr = str.substr(length - 3);
        if (typeStr == "pdf" || typeStr == "txt" || typeStr == "doc" || typeStr == "bin" || typeStr == "ach" || typeStr == "zip") return false;
    }
    return true;
}
