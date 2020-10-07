#include"total.h"
#include"PointManager.h"
#include"BezierDrawer.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>

#define CannotResize  (sf::Style::Titlebar |  sf::Style::Close)
#define KeyPressing sf::Event::KeyPressed
#define KeyReleasing sf::Event::KeyReleased
#define KeyEvent(EV) (sf::Keyboard::isKeyPressed(EV))

int dragPoint()
{
	unsigned int width = 1024, height = 768;
	/*std::cout << "Bezier曲线演示(去递归)，通过鼠标点按窗口内空间添加控制点\n\n";
	system("pause");*/

	sf::RenderWindow App(sf::VideoMode(width, height),
		"Bezier", sf::Style::Close | sf::Style::Titlebar);

	bool isInsert = false;

	bf::PointManager pm;

	bf::BezierDrawer bDrawer(pm, 8000);

	while (App.isOpen())
	{
		bf::Time::tmpDeltaTime = std::clock();
		sf::Event ev;
		while (App.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed || (KeyPressing && KeyEvent(sf::Keyboard::Key::Escape)))
			{
				App.close();
			}
		}

		isInsert = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

		pm.Update(App.mapPixelToCoords(sf::Mouse::getPosition(App)), isInsert);

		bDrawer.Update();
		
		App.clear(sf::Color(40, 40, 40, 255));

		App.draw(pm);

		App.draw(bDrawer);

		App.display();

		bf::Time::deltaTime = std::clock() - bf::Time::tmpDeltaTime;
		bf::Time::totalTime += bf::Time::deltaTime;
	}
	return 0;
}