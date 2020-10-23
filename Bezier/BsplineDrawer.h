#pragma once
#include"PointManager.h"
using std::cout;
using std::endl;
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

			tLength = pow(2, degree) - 1;
			tArray = (int*)malloc(sizeof(int) * tLength);
			tArray[0] = 0;
			for (size_t i = 1; i < tLength; i++)
			{
				tArray[i] = i % 2 != 0 ? tArray[(i - 1) / 2] : tArray[(i - 2) / 2] + 1;
				cout << tArray[i] << " ";
			}
			cout << endl;
		}

		//节点向量
		vector<float> knot;

		int degree;//三阶

		Vector2f points[6];

		void Update()
		{
			if (pManager.isUpdate)
			{
				UpdateKnot();
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
							//N_i_k = BaseFunc_RE(j, degree - 1, tMin + (i * dt));
							outKnot("递归结果: ", j, degree - 1, N_i_k);
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
		i: 控制点
		k: 次数
		u: 节点
		*/
		float BaseFunc(int i, int k, float u)
		{
			int k_2 = pow(2, k);
			int rk = 0;
			for (int it = 0; it < k_2; it++)
			{
				if (it >= uArray.size())
				{
					uArray.push_back(0);
				}
			}
			for (int it = 0; it < k_2; it += 1)
			{
				uArray[it] = (u >= knot[i + tArray[index(k, it)]]
					&& u < knot[i + tArray[index(k, it)] + 1]) ? 1.0f : 0.0f;
			}
			rk++;
			float div1, div2, U1, U2;
			while (rk <= k)
			{
				for (int it = 0; it < k_2; it += 2)
				{
					div1 = knot[i + tArray[index(k - rk, it)] + rk] - knot[i + tArray[index(k - rk, it)]];
					div2 = knot[i + tArray[index(k - rk, it)] + rk + 1] - knot[i + tArray[index(k - rk, it)] + 1];

					U1 = (abs(div1) < 1e-3f) ? 1.0f : (u - knot[i + tArray[index(k - rk, it)]]) / div1;
					U2 = (abs(div2) < 1e-3f) ? 1.0f : (knot[i + tArray[index(k - rk, it)] + rk + 1] - u) / div2;

					uArray[it / 2] = U1 * uArray[it] + U2 * uArray[it + 1];

				}
				k_2 /= 2;
				rk++;
			}
			return uArray[0];
		}

		int index(int k, int it)
		{
			return (int)pow(2, k) - 1 + it;
		}

		float BaseFunc_RE(int i, int k, float u)
		{
			if (k == 0)
			{
				/*std::cout << "u(" << u << ") >= [" << i << "](" << knot[i]
					<< ") && u(" << u << ") < [" << i + 1 << "](" << knot[i + 1] << ")\n";*/
					/*std::cout << (u > knot[i] && u <= knot[i + 1]) << std::endl;*/
				return (u >= knot[i] && u < knot[i + 1]) ? 1.0f : 0.0f;
			}

			float div1 = knot[i + k] - knot[i];
			float div2 = knot[i + k + 1] - knot[i + 1];

			float U1 = (div1 <= 1e-3) ? 1.0f : (u - knot[i]) / div1;
			float U2 = (div2 <= 1e-3) ? 1.0f : (knot[i + k + 1] - u) / div2;

			float a = BaseFunc_RE(i, k - 1, u);
			outKnot("", i, k - 1, a);
			float b = BaseFunc_RE(i + 1, k - 1, u);
			outKnot("", i + 1, k - 1, b);
			return U1 * a + U2 * b;
		}

		void UpdateKnot()
		{
			int knotCount = pManager.points.size() + degree;
			for (int i = 0; i < knotCount; i++)
			{
				if (i < knot.size())
				{
					knot[i] = (float)i / (knotCount - 1);
					/*if (i < degree)
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
					}*/
				}
				else
				{
					knot.push_back((float)i / (knotCount - 1));
					/*if (i < degree)
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
					}*/
				}
			}
		}

	private:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
		{
			target.draw(vertexs, states);
		}

		void outKnot(string const& attatch, int const& i, int const& k, float const& val)
		{
			std::cout << attatch << "[" << i << ", " << k << "]: " << val << std::endl;
		}

		sf::VertexArray vertexs;
		PointManager& pManager;
		int lCount;

		vector<float> uArray;

		int* tArray;

		int tLength;

	};

}
