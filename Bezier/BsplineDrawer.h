#pragma once
#include"PointManager.h"
namespace bf
{
	class BsplineDrawer : public sf::Drawable
	{
	public:

		BsplineDrawer(PointManager& pointManager, int lampCount)
			:pManager(pointManager), lCount(lampCount)
		{
			vertexs = sf::VertexArray(sf::PrimitiveType::LineStrip, lCount);
			degree = 3;
		}

		void Init()
		{
			/*points[0] = { 100,100 };
			points[1] = { 150,200 };
			points[2] = { 200,100 };
			points[3] = { 250,200 };
			points[4] = { 300,100 };
			points[5] = { 350,200 };*/
			//pManager.ForbidenInsert(true);
			/*for (size_t i = 0; i < 6; i++)
			{
				pManager.InserPointNormal(points[i]);
			}*/
		}

		//�ڵ�����
		vector<float> knot;

		int degree = 3;//����

		Vector2f points[6];

		void Update()
		{
			if (pManager.isUpdate)
			{
				SetKnot();
				Vector2f tmpPos;

				float tMin = knot[degree - 1];
				float tMax = knot[knot.size() - degree];

				float dt = (tMax - tMin) / (lCount - 1);
				float N_i_k = 0;

				for (int i = 0; i < lCount; i++)
				{
					if (pManager.points.size() >= 2)
					{
						tmpPos = { 0.0f,0.0f };
						for (int j = 0; j < pManager.points.size(); j++)
						{
							N_i_k = BaseFunc(j, degree - 1, tMin + (i * dt));
							//std::cout << i << ", j: " << j << ", n" << N_i_k << std::endl;
							tmpPos += N_i_k * pManager.points[j].pos;
						}
						vertexs[i].position = tmpPos;
					}
					else
					{
						vertexs[i].position = { 0.0f,0.0f };
					}
					vertexs[i].color = Color::White;
				}
				pManager.isUpdate = false;
			}
		}

		/*
		Bspline base function constructor
		i: ���Ƶ�
		k: ����
		u: �ڵ�
		*/
		float BaseFunc(int i, int k, float u)
		{
			if (k == 0)
			{
				/*std::cout << "u(" << u << ") >= [" << i << "](" << knot[i]
					<< ") && u(" << u << ") < [" << i + 1 << "](" << knot[i + 1] << ")\n";
				std::cout << (u > knot[i] && u <= knot[i + 1]) << std::endl;*/
				return (u >= knot[i] && u < knot[i + 1]) ? 1.0f : 0.0f;
			}

			float div1 = knot[i + k] - knot[i];
			float div2 = knot[i + k + 1] - knot[i + 1];

			float U1 = (div1 <= 1e-3) ? 1.0f : (u - knot[i]) / div1;
			float U2 = (div2 <= 1e-3) ? 1.0f : (knot[i + k + 1] - u) / div2;

			return U1 * BaseFunc(i, k - 1, u) + U2 * BaseFunc(i + 1, k - 1, u);
		}

		void SetKnot()
		{
			int knotCount = pManager.points.size() + degree;
			for (int i = 0; i < knotCount; i++)
			{
				if (i < knot.size())
				{
					//knot[i] = (float)i / (knotCount - 1);
					if (i < degree)
					{
						knot[i] = i;
					}
					else if (i <= knotCount - degree)
					{
						knot[i] = knot[i - 1] + 1;
					}
					else
					{
						knot[i] = knot[i - 1];
					}
				}
				else
				{
					//knot.push_back((float)i / (knotCount - 1));
					if (i < degree)
					{
						knot.push_back((float)i);
					}
					else if (i <= knotCount - degree)
					{
						knot.push_back(knot[i - 1] + 1);
					}
					else
					{
						knot.push_back(knot[i - 1]);
					}
				}
			}
		}

	private:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
		{
			target.draw(vertexs, states);
		}

		sf::VertexArray vertexs;
		PointManager &pManager;
		int lCount;
	};

}
