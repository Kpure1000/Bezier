#pragma once
#include<SFML/Graphics.hpp>
using sf::Vector2f;
using sf::Vector2i;
using sf::Color;

#define VECTOR_DISTANCE(a,b) sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y))

namespace bf
{
	//���Ƶ�����
	enum class PointType
	{
		Normal,	//��ͨ
		Top,	// �˵�
		Fixed,	// �̶��㣨B������
		Rotate	// ��ת�㣨B������
	};
	//���Ƶ�
	class Point : public sf::Drawable
	{
	public:
		Point() :
			pType(PointType::Normal), pos(), rRedius(), cRedius(), nColor(), hColor() {}
		Point(PointType pointType, Vector2f const& Position, float RenderRedius, float CheckRedius, Color normalColor, Color highlightColor) :
			pType(pointType), pos(Position), rRedius(RenderRedius), cRedius(CheckRedius), nColor(normalColor), hColor(highlightColor)
		{
			rShape.setPosition(pos);
			rShape.setRadius(rRedius);
			rShape.setOutlineThickness(rRedius * 0.4f);
			rShape.setOrigin(rRedius, rRedius);

			rShape.setFillColor(nColor);
			rShape.setOutlineColor(nColor);
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

		//����״̬��ɫ
		void setHighlight(bool isHighlight) { isHighlight ? rShape.setOutlineColor(hColor) : rShape.setOutlineColor(nColor); }
		/*  */

		PointType pType;

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

