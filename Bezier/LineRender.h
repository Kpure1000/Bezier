#pragma once
#include<vector>
#include<iostream>
#include<SFML/Graphics.hpp>
class LineRender : public sf::Drawable
{
public:

	/*
	* a,bΪ�˵�
	* lampCount��ֵ��Ŀ
	*/
	LineRender(int const& lampCount)
	{
		std::cout << "��ʼ����Bezier���ߣ�(��ֵ����: " << lampCount << ")" << std::endl;
		this->lampCount = lampCount;
		line = sf::VertexArray(sf::PrimitiveType::LineStrip, lampCount);
		for (size_t i = 0; i < lampCount; i++)
		{
			line[i].color = sf::Color::White;
		}
	}

	void InsertController(sf::Vector2f newController)
	{
		//���Ƶ���ʾ
		sf::CircleShape newPoint(3.0f);
		newPoint.setOrigin(newPoint.getRadius(), newPoint.getRadius());
		newPoint.setPosition(newController);
		newPoint.setFillColor(sf::Color::White);
		pointers.push_back(newPoint);

		//���Ƶ����
		sf::Vector2f last;
		if (ctrlPoints.size() >= 2)
		{
			//����Ѿ������������˵㣬��������˵��м䣨ָ���飩��ʼ����
			last = ctrlPoints.back();
			ctrlPoints.pop_back();
			ctrlPoints.push_back(newController);
			ctrlPoints.push_back(last);
		}
		else
		{
			//����˵�
			ctrlPoints.push_back(newController);
		}

		//��������
		for (size_t i = 0; i < ctrlPoints.size(); i++)
		{
			if (i < tmpPoints.size())
			{
				tmpPoints[i] = ctrlPoints[i];
			}
			else
			{
				tmpPoints.push_back(ctrlPoints[i]);
			}
		}

		std::cout << "Add a controller. counts: " << pointers.size() << std::endl;

		//��Ҫ���¼�������
		isFound = false;
	}

	void Update()
	{
		if (isFound)
			return;
		float dt = 0;
		//���Բ�ֵ��������
		for (size_t i = 0; i < lampCount; i++)
		{
			//Ѱ��Ŀ���
			if (ctrlPoints.size() >= 2)
			{
				//line[i].position = findTarget(0, ctrlPoints.size() - 1, dt); //�ݹ鷽��
				line[i].position = findTarget(dt); //  ��������
			}
			else
			{
				line[i].position = { 0,0 };
			}
			dt += (float)(1.0f / lampCount);
		}
		isFound = true;
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
	{
		target.draw(line, states);
		for (size_t i = 0; i < pointers.size(); i++)
		{
			target.draw(pointers[i], states);
		}
	}

	/*
	* Ѱ��Ŀ���(�ݹ�ʵ��)
	*/
	sf::Vector2f findTarget(int const& i, int const& r, float const& t)
	{
		if (r <= 0)
			return ctrlPoints[i];
		return ((1 - t) * findTarget(i, r - 1, t) + t * findTarget(i + 1, r - 1, t));
	}

	/*
	* Ѱ��Ŀ���(����ʵ��)
	*/
	sf::Vector2f findTarget(float const& t)
	{
		for (size_t i = tmpPoints.size(); i >= 1; i--)
		{
			for (size_t j = 0; j + 1 < i; j++)
			{
				tmpPoints[j] = (1 - t) * tmpPoints[j] + t * tmpPoints[j + 1];
			}
		}
		if (tmpPoints.size() > 0)
		{
			return tmpPoints[0];
		}
		return { 0,0 };
	}

	std::vector<sf::Vector2f> ctrlPoints;

	//����Ŀ��Ƶ㣨����������
	std::vector<sf::Vector2f> tmpPoints;

	int lampCount;

	sf::VertexArray line;

	sf::Vector2f mousePos;

	std::vector<sf::CircleShape> pointers;

	bool isFound;
};

