#pragma once
#include"PointManager.h"
namespace bf
{
	class BezierDrawer : public sf::Drawable
	{
	public:
		BezierDrawer(PointManager& pointManager, int lampCount) :
			pManager(pointManager), lCount(lampCount)
		{
			line = sf::VertexArray(sf::PrimitiveType::LineStrip, lCount);
			for (size_t i = 0; i < lCount; i++)
			{
				line[i].color = sf::Color::White;
			}
		}

		void Update()
		{
			if (pManager.isUpdate)
			{
				float dt = 0;
				for (size_t i = 0; i < lCount; i++)
				{
					//寻找目标点
					if (pManager.points.size() >= 2)
					{
						line[i].position = findTarget(dt); //  迭代方法
					}
					else
					{
						line[i].position = { 0,0 };
					}
					dt += (float)(1.0f / lCount);
				}
				pManager.isUpdate = false;
			}
			//}
		}

	private:

		Vector2f findTarget(float const& t)
		{
			for (size_t i = pManager.tmpPoints.size(); i >= 1; i--)
			{
				for (size_t j = 0; j + 1 < i; j++)
				{
					pManager.tmpPoints[j].pos = (1 - t) * pManager.tmpPoints[j].pos +
						t * pManager.tmpPoints[j + 1].pos;
				}
			}
			if (pManager.tmpPoints.size() > 0)
			{
				return pManager.tmpPoints[0].pos;
			}
			return { 0,0 };
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
		{
			target.draw(line, states);
		}

		PointManager& pManager;

		sf::VertexArray line;

		int lCount;

	};
}


