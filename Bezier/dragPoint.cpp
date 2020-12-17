#include"total.h"
#include"PointManager.h"
#include"BezierDrawer.h"
#include"BsplineDrawer.h"
#include"AssetManager.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include<vector>

int dragPoint()
{
	unsigned int width = 1024, height = 768;

	sf::RenderWindow App(sf::VideoMode(width, height),
		"B-Spline Sketcher", sf::Style::Close | sf::Style::Titlebar);
	
	sf::Vector2u wsize = App.getSize();
	
	sf::View painter(sf::FloatRect(0, 0, wsize.x * 0.8f, wsize.y));
	painter.setViewport(sf::FloatRect(0, 0, 0.8f, 1.f));

	sf::View Gui(sf::FloatRect(0, 0, wsize.x * 0.2f, wsize.y));
	Gui.setViewport(sf::FloatRect(0.8f, 0.0f, 0.2f, 1.0f));

	//���Ƶ����
	bf::PointManager pm;

	//���������߻���
	//bf::BezierDrawer bDrawer(pm, 10000);

	bf::BsplineDrawer bSpliner(pm, 100);

	sf::Text t_scrScale("scale: ", AssetManager::getInstance()->GetFont(FONT_MSYH), 24u);

	char str[64];

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

#pragma region ���ֵ���������ͼ����

			ViewSize = painter.getSize();
			ViewScale = ViewSize.y / wsize.y;

			if (ev.mouseWheelScroll.delta == 1 and ViewScale > 0.5)
			{
				painter.setSize(ViewSize.x / 1.02, ViewSize.y / 1.02);
			}
			if (ev.mouseWheelScroll.delta == -1 and ViewScale < 10)
			{
				painter.setSize(ViewSize.x * 1.02, ViewSize.y * 1.02);
			}

#pragma endregion
			
		}

		App.clear(sf::Color(40, 40, 40, 255));

#pragma region ����

		App.setView(painter);
		//���¿��Ƶ�
		pm.Update(App, sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
		//�������߲�ֵ
		//bDrawer.Update();
		bSpliner.Update();
		//���ƿ��Ƶ�
		App.draw(pm);
		//��������
		//App.draw(bDrawer);
		App.draw(bSpliner);

#pragma endregion

#pragma region GUI

		App.setView(Gui);

		ViewScale = ViewSize.y / wsize.y;
		sprintf_s(str, "B-Spline Sketch!\r\nView Scale: %.2f", ViewScale);
		t_scrScale.setString(str);

		//���������ı�
		App.draw(t_scrScale);

#pragma endregion

		App.display();

		bf::Time::deltaTime = std::clock() - bf::Time::tmpDeltaTime;
		bf::Time::totalTime += bf::Time::deltaTime;
	}
	return 0;
}