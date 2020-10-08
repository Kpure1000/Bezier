#pragma once
#include<vector>
#include<iostream>
#include"Point.h"
#include"Time.h"
using std::vector;
namespace bf
{
	class PointManager : public sf::Drawable
	{
	public:
		/// <summary>
		/// ����
		/// </summary>
		/// <param name="mousePosition"></param>
		void Update(Vector2f const& mousePosition, bool& isPressed)
		{
			if (!isDraged)
			{
				for (int i = 0; i < points.size(); i++)
				{
					//�Ƿ���ĳ��ļ�ⷶΧ��
					isInRange = points[i].isContained(mousePosition);
					//���ø߹�
					points[i].setHighlight(isInRange);
					if (isInRange && isPressed && !isDraged) {
						//std::cout << "�ڷ�Χ��: " << mousePosition.x << ", " << mousePosition.y << "\n";
						isDraged = true;
						dragPoint = &points[i];
						//������
						isInserted = true;
					}
				}
			}
			else
			{
				dragPoint->Update(mousePosition);
				//�����˿��Ƶ�
				isUpdate = true;
			}
			if (isPressed)
			{
				if (!isInserted)
				{
					isInserted = true;
					if (points.size() >= 2)
					{
						InsertPoint(mousePosition, PointType::Normal);
					}
					else
					{
						InsertPoint(mousePosition, PointType::Top);
					}
				}
			}
			else
			{
				isDraged = false;
				isInserted = false;
				dragPoint = nullptr;
			}
			for (size_t i = 0; i < points.size(); i++)
			{
				if (i < tmpPoints.size())
				{
					tmpPoints[i] = points[i];
				}
				else
				{
					tmpPoints.push_back(points[i]);
				}
			}
		}

		//�Ƿ�����˿��Ƶ�
		bool isUpdate = false;

		vector<Point> points;
		vector<Point> tmpPoints;

		const float normalRenderR = 3.5f;
		const float topRenderR = 4.5f;
		const float checkR = 6.0f;
		const Color normalColor = Color(0x007777ff);
		const Color highlightColor = Color(0xff0000ff);

	private:
		void InsertPoint(Vector2f const& pos, PointType type)
		{
			//std::cout << "���:(" << pos.x << ", " << pos.y << ")\n";
			Point last;
			if (type == PointType::Normal)
			{
				last = points.back();
				points.pop_back();
				points.push_back(Point(type, pos, normalRenderR, checkR, normalColor, highlightColor));
				points.push_back(last);
			}
			else
			{
				points.push_back(Point(type, pos, topRenderR, checkR, normalColor, highlightColor));
			}
			//�����˿��Ƶ�
			isUpdate = true;
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
		{
			for (size_t i = 0; i < points.size(); i++)
			{
				target.draw(points[i], states);
			}
		}

		/* �����Ϊ��� */
		bool isInRange = false;

		bool isInserted = false;

		bool isDraged = false;

		Point* dragPoint = nullptr;
	};
}

