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
		void Update(sf::RenderWindow& App, bool const& isPressed)
		{
			m_mousePosition = App.mapPixelToCoords(sf::Mouse::getPosition(App));
			wsize = App.getSize();
			if (!isDraged)
			{
				for (int i = 0; i < points.size(); i++)
				{
					//是否在某点的检测范围内
					isInRange = points[i].isContained(m_mousePosition);
					//设置高光
					points[i].setHighlight(isInRange);
					if (isInRange && isPressed && !isDraged) {
						//std::cout << "在范围内: " << mousePosition.x << ", " << mousePosition.y << "\n";
						isDraged = true;
						dragPoint = &points[i];
						//插入了
						isInserted = true;
					}
				}
			}
			else
			{
				dragPoint->Update(m_mousePosition);
				//更新了控制点
				isUpdate = true;
			}
			if (isPressed)
			{
				if (!isForbidenInsert && !isInserted && (m_mousePosition.x > 0 && m_mousePosition.x < wsize.x * 0.8
						&& m_mousePosition.y > 0 && m_mousePosition.y < wsize.y))
				{
					isInserted = true;
					if (points.size() >= 2)
					{
						InsertPoint(m_mousePosition, PointType::Normal);
					}
					else
					{
						InsertPoint(m_mousePosition, PointType::Top);
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

		void InsertPoint(Vector2f const& pos, PointType type)
		{
			if (isForbidenInsert)return;
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
				points.push_back(Point(type, pos, topRenderR, checkR, normalColor, highlightColor));
			}
			//更新了控制点
			isUpdate = true;
		}

		void InserPointNormal(Vector2f const& pos)
		{
			points.push_back(Point(PointType::Normal, pos, normalRenderR, checkR, normalColor, highlightColor));
			isUpdate = true;
		}

		void ForbidenInsert(bool isF)
		{
			isForbidenInsert = isF;
		}

		//是否更新了控制点
		bool isUpdate = false;

		vector<Point> points;
		vector<Point> tmpPoints;

		const float normalRenderR = 3.5f;
		const float topRenderR = 4.5f;
		const float checkR = 6.0f;
		const Color normalColor = Color(0x007777ff);
		const Color highlightColor = Color(0xff0000ff);

	private:
		

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
		{
			for (size_t i = 0; i < points.size(); i++)
			{
				target.draw(points[i], states);
			}
		}

		sf::Vector2f m_mousePosition;

		sf::Vector2u wsize;

		/* 鼠标行为相关 */
		bool isInRange = false;

		bool isInserted = false;

		bool isDraged = false;

		bool isForbidenInsert = false;

		Point* dragPoint = nullptr;
	};
}

