#include "Interface.h"

void music() {
	PlaySound(L"music/relax.wav", NULL, SND_FILENAME);
}
void goodBye() {
	std::cout <<"      DEAR USER!\n";
	Sleep(1500);
	std::cout << " >>THANK YOU FOR CHOOSING THIS PROGRAMM\n";
	Sleep(1500);
	std::cout << " >>HAVE A NICE DAY!\n";
	Sleep(1500);
	std::cout << "...\n";
	Sleep(1500);
	std::cout << "        =)";
	return;
}
void menu(RenderWindow& window)
{
	Image icon;
	icon.loadFromFile("images/icon.png");
	window.setIcon(50, 50, icon.getPixelsPtr());
	int flag = 1;
	Texture menuTexture_create, menuTexture_decrypt, menuTexture_exit, aboutTexture, aboutTexture_info, aboutTexture_press, menuBackground;
	menuTexture_create.loadFromFile("images/create.png");
	menuTexture_decrypt.loadFromFile("images/decrypt.png");
	menuTexture_exit.loadFromFile("images/exit.png");
	aboutTexture.loadFromFile("images/about.png");
	aboutTexture_info.loadFromFile("images/info.png");
	aboutTexture_press.loadFromFile("images/press.png");
	menuBackground.loadFromFile("images/menu.png");
	Sprite menu_createButtom(menuTexture_create), menu_decryptButtom(menuTexture_decrypt), menu_exitButtom(menuTexture_exit), menu_background(menuBackground);
	Sprite menu_aboutButtom(aboutTexture), about_info(aboutTexture_info), about_press(aboutTexture_press);
	bool MENU = true;
	int userChoice = 0;

	menu_createButtom.setPosition(50, 180);
	menu_decryptButtom.setPosition(45, 270);
	menu_aboutButtom.setPosition(40, 360);

	menu_exitButtom.setPosition(580, 500);
	menu_background.setPosition(230, 40);


	Font font;
	font.loadFromFile("fonts/font.otf");
	Text text("", font, 35);

			while (MENU)
			{
				while (window.isOpen())
				{
					Event event;
					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed)
						{
							window.close();
							return;
						}

				flag = 1;
				menu_createButtom.setColor(Color::White);
				menu_decryptButtom.setColor(Color::White);
				menu_aboutButtom.setColor(Color::White);
				menu_exitButtom.setColor(Color::White);
				menu_aboutButtom.setPosition(40, 360);

				userChoice = 0;

				window.clear(Color(69, 53, 88));
				if (IntRect(50, 180, 400, 70).contains(Mouse::getPosition(window))) {
					menu_createButtom.setColor(Color(255, 215, 0)); userChoice = 1;
				}
				if (IntRect(45, 270, 400, 70).contains(Mouse::getPosition(window))) {
					menu_decryptButtom.setColor(Color(255, 215, 0)); userChoice = 2;
				}
				if (IntRect(40, 360, 400, 70).contains(Mouse::getPosition(window))) {
					menu_aboutButtom.setColor(Color(255, 215, 0)); userChoice = 3;
				}

				if (IntRect(580, 500, 120, 45).contains(Mouse::getPosition(window))) {
					menu_exitButtom.setColor(Color(255, 0, 0)); userChoice = 4;
				}

				if (Mouse::isButtonPressed(Mouse::Left))
				{
					if (userChoice == 1) {
						text.setStyle(sf::Text::Bold);
						text.setString("[Follow the instructions in the console]");
						text.setPosition(34, 220);
						window.draw(text);
						window.display();
						flag = encryptionFunc(window);
						while (flag != 0);
					}
					if (userChoice == 2) {
						text.setStyle(sf::Text::Bold);
						text.setString("[Follow the instructions in the console]");
						text.setPosition(34, 220);
						window.draw(text);
						window.display();
						flag=DencryptionFunc();
						while (flag != 0);
					}
					if (userChoice == 3) {
						window.clear(Color(47, 79, 79));
						menu_aboutButtom.setColor(Color(218, 165, 32));

						menu_aboutButtom.setPosition(140, 10);
						about_info.setPosition(15, 120);
						about_press.setPosition(15, 480);

						window.draw(about_info);
						window.draw(menu_aboutButtom);
						window.draw(about_press);
						window.display();
						while (!Keyboard::isKeyPressed(Keyboard::Escape));
					}

					if (userChoice == 4) { window.close(); MENU = false; }
				}
				window.draw(menu_background);
				window.draw(menu_createButtom);
				window.draw(menu_decryptButtom);
				window.draw(menu_aboutButtom);

				window.draw(menu_exitButtom);
				window.display();
			}
		}
	}
			
}

