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
		/// 更新
		/// </summary>
		/// <param name="mousePosition"></param>
		void Update(Vector2f const& mousePosition, bool isPressed)
		{
			if (!isDraged)
			{
				for (int i = 0; i < points.size(); i++)
				{
					//是否在某点的检测范围内
					isInRange = points[i].isContained(mousePosition);
					//设置高光
					points[i].setHighlight(isInRange);
					if (isInRange && isPressed && !isDraged) {
						//std::cout << "在范围内: " << mousePosition.x << ", " << mousePosition.y << "\n";
						isDraged = true;
						dragPoint = &points[i];
						isInserted = true;
					}
				}
			}
			else
			{
				dragPoint->Update(mousePosition);
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
				dragPoint = nullptr;
				isInserted = false;
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

		bool isUpdate = false;

		vector<Point> points;
		vector<Point> tmpPoints;

		const float normalRenderR = 4.0f;
		const float topRenderR = 5.0f;
		const float checkR = 5.0f;
		const Color normalColor = Color(0x007777ff);
		const Color highlightColor = Color(0xff0000ff);

	private:
		void InsertPoint(Vector2f const& pos, PointType type)
		{
			//std::cout << "添加:(" << pos.x << ", " << pos.y << ")\n";
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
				points.push_back(Point(type, pos, normalRenderR, checkR, normalColor, highlightColor));
			}
			isUpdate = true;
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
		{
			for (size_t i = 0; i < points.size(); i++)
			{
				target.draw(points[i], states);
			}
		}

		/* 鼠标行为相关 */
		bool isInRange = false;

		bool isInserted = false;

		bool isDraged = false;

		Point* dragPoint = nullptr;
	};
}

