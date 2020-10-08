#include<SFML/Graphics.hpp>
#include<vector>
#include"LineRender.h"
#include"total.h"

unsigned int width = 1024, height = 768;

int bezier_simple_main()
{
	std::cout << "Bezier曲线演示(去递归)，通过鼠标点按窗口内空间添加控制点\n\n";
	system("pause");

	sf::RenderWindow App(sf::VideoMode(width, height),
		"Bezier", sf::Style::Close | sf::Style::Titlebar);

	LineRender line(15000);

	while (App.isOpen())
	{
		sf::Event ev;
		while (App.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed || (KeyPressing && KeyEvent(sf::Keyboard::Key::Escape)))
			{
				App.close();
			}
			if (ev.type == sf::Event::MouseButtonPressed)
			{
				line.InsertController(App.mapPixelToCoords(sf::Mouse::getPosition(App)));
			}
		}

		App.clear(sf::Color(40, 40, 40, 255));

		line.Update();

		App.draw(line);

		App.display();
	}
	return 0;
}