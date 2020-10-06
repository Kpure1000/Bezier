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
		//设置位置
		void setPosition(Vector2f const& newPosition) { 
			rShape.setPosition(newPosition);
			pos = newPosition;
		}
		//获取位置
		Vector2f getPosition() { return pos; }
		//设置状态颜色
		void setStatusColor(bool isHighlight) { isHighlight ? rShape.setOutlineColor(hColor) : rShape.setOutlineColor(nColor); }
		/*  */

	private:

		//位置
		Vector2f pos;

		//普通颜色
		Color nColor;
		//高亮颜色
		Color hColor;

		//实际渲染半径
		float rRedius;
		//检测半径
		float cRedius;

		sf::CircleShape rShape;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
		{
			target.draw(rShape, states);
		}
	};

}

