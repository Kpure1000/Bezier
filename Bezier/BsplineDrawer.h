#pragma once
#include"PointManager.h"
namespace bf
{
	class BsplineDrawer
	{
	public:
		vector<float>NodeVector;

		float BaseFunc(int i, int k, float u)
		{
			if (k == 0) {
				if ((u >= NodeVector[i + 1]) && (u < NodeVector[i + 2])) {
					return 1.0f;
				}
				else {
					return 0.0f;
				}
			}
			else {
				length1 = NodeVector[i + k + 1] - NodeVector[i + 1];
				length2 = NodeVector[i + k + 2] - NodeVector[i + 2];
				abs(length1) <= 1e-7f ? length1 = 1.f : 0.f;
				abs(length2) <= 1e-7f ? length2 = 1.f : 0.f;

				return (u - NodeVector[i + 1] / length1 * BaseFunc(i, k - 1, u))
					+ (NodeVector[i + k + 2] - u) / length2 * BaseFunc(i + 1, k - 1, u);
			}

		}


	private:
		float length1;
		float length2;
	};

}
