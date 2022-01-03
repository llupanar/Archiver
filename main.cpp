#include "Interface.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
//	system("chcp 1251");
	//system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 103);
	system("title Archiver console");
	system("mode con cols=70 lines=23");
	thread interfaceMusic(music);
	sf::RenderWindow window(sf::VideoMode(700, 550), "Archiver", sf::Style::Default);
	window.setFramerateLimit(60);
	menu(window);
	goodBye();
	interfaceMusic.join();
	return 0;
}