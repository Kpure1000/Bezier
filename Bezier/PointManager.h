#pragma once
#include<vector>
#include"Point.h"
using std::vector;
namespace bf
{
	class PointManager
	{
	public:

		void Update(Vector2i mousePosition)
		{
			for (int i = 0; i < points.size(); i++)
			{
				//是否在某点的检测范围内
				if (points[i].isContained(mousePosition))
				{

				}
			}
		}

		void InsertPoint(Vector2f pos)
		{
			points.push_back(Point(pos, normalRenderR, checkR, normalColor, highlightColor));
		}

		vector<Point> points;

		const float normalRenderR = 2;
		const float topRenderR = 3;
		const float checkR = 2.2f;
		const Color normalColor;
		const Color highlightColor;
	};
}

