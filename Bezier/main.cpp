#include<SFML/Graphics.hpp>
#include<vector>
#include"LineRender.h"

unsigned int width = 1024, height = 768;
#define CannotResize  (sf::Style::Titlebar |  sf::Style::Close)
#define KeyPressing sf::Event::KeyPressed
#define KeyReleasing sf::Event::KeyReleased
#define KeyEvent(EV) (sf::Keyboard::isKeyPressed(EV))
int main()
{
	std::cout << "Bezier曲线演示(去递归)，通过鼠标点按窗口内空间添加控制点\n\n";
	system("pause");

	sf::RenderWindow App(sf::VideoMode(width, height),
		"Bezier", sf::Style::Close | sf::Style::Titlebar);

	std::vector<sf::Vector2f> vertexs;

	sf::Vector2f mousePos;

	LineRender line(10000);

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
}