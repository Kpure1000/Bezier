#include"total.h"
#include"PointManager.h"
#include"BezierDrawer.h"
#include"AssetManager.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>


int dragPoint()
{
	unsigned int width = 1024, height = 768;
	/*std::cout << "Bezier曲线演示(去递归)，通过鼠标点按窗口内空间添加控制点\n\n";
	system("pause");*/

	sf::RenderWindow App(sf::VideoMode(width, height),
		"Bezier", sf::Style::Close | sf::Style::Titlebar);
	
	auto wsize = App.getSize();
	
	sf::View camera(sf::FloatRect(0, 0, wsize.x, wsize.y));

	App.setView(camera);

	bool isInsert = false;

	bf::PointManager pm;

	bf::BezierDrawer bDrawer(pm, 3000);

	sf::Text t_scrScale("scale: ", AssetManager::getInstance()->GetFont(FONT_MSYH), 30u);

	char str[32];

	float ViewScale;
	sf::Vector2f ViewSize;

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

			ViewSize = camera.getSize();

			ViewScale = ViewSize.y / App.getSize().y;

			if (ev.mouseWheelScroll.delta == 1 and ViewScale > 0.5)
			{
				camera.setSize(ViewSize.x / 1.02, ViewSize.y / 1.02);
			}
			if (ev.mouseWheelScroll.delta == -1 and ViewScale < 10)
			{
				camera.setSize(ViewSize.x * 1.02, ViewSize.y * 1.02);
			}
		}

		isInsert = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

		pm.Update(App.mapPixelToCoords(sf::Mouse::getPosition(App)), isInsert);

		bDrawer.Update();

		App.setView(camera);

		ViewScale = ViewSize.y / App.getSize().y;
		sprintf_s(str, "View Scale: %.2f", ViewScale);
		t_scrScale.setScale(ViewScale, ViewScale);
		t_scrScale.setPosition(width * (1 - ViewScale) / 2, height * (1 - ViewScale) / 2);

		t_scrScale.setString(str);

		App.clear(sf::Color(40, 40, 40, 255));
		
		

		App.draw(t_scrScale);

		App.draw(pm);

		App.draw(bDrawer);

		App.display();

		bf::Time::deltaTime = std::clock() - bf::Time::tmpDeltaTime;
		bf::Time::totalTime += bf::Time::deltaTime;
	}
	return 0;
}