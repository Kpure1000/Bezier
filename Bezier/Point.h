#pragma once
#include<SFML/Graphics.hpp>
using sf::Vector2f;
using sf::Vector2i;
using sf::Color;

#define VECTOR_DISTANCE(a,b) sqrtf((a.x - b.x, 2)*(a.x - b.x, 2) - (a.y - b.x, 2)*(a.y - b.x, 2))

namespace bf
{
	class Point : sf::Drawable
	{
	public:

		Point(Vector2f const& Position, float RenderRedius, float CheckRedius, Color normalColor, Color highlightColor) :
			pos(Position), rRedius(RenderRedius), cRedius(CheckRedius), nColor(normalColor), hColor(highlightColor)
		{
			rShape.setPosition(Position);
			rShape.setOutlineThickness(rRedius * 0.3f);
			rShape.setFillColor(normalColor);
			rShape.setOutlineColor(normalColor);
		}

		bool isContained(Vector2i const& targetPosition)
		{
			isContained(static_cast<Vector2f>(targetPosition));
		}

		bool isContained(Vector2f const& targetPosition)
		{
			return (VECTOR_DISTANCE(targetPosition, pos) < cRedius);
		}

		void Update(Vector2i const& newPositon)
		{
			Update(static_cast<Vector2f>(newPositon));
		}

		void Update(Vector2f const& newPositoin)
		{
			pos = newPositoin;
			rShape.setPosition(newPositoin);
		}
		//����λ��
		void setPosition(Vector2f const& newPosition) { 
			rShape.setPosition(newPosition);
			pos = newPosition;
		}
		//��ȡλ��
		Vector2f getPosition() { return pos; }
		//����״̬��ɫ
		void setStatusColor(bool isHighlight) { isHighlight ? rShape.setOutlineColor(hColor) : rShape.setOutlineColor(nColor); }
		/*  */

	private:

		//λ��
		Vector2f pos;

		//��ͨ��ɫ
		Color nColor;
		//������ɫ
		Color hColor;

		//ʵ����Ⱦ�뾶
		float rRedius;
		//���뾶
		float cRedius;

		sf::CircleShape rShape;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
		{
			target.draw(rShape, states);
		}
	};

}

