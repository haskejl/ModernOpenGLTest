#pragma once

#include "Logger.h"
#include "Math.h"

namespace ssfw
{
	struct Triangle
	{
		Vec3D<float> v[3];
		Vec3D<float> normal;

		Triangle(Vec3D<float> vin0, Vec3D<float> vin1, Vec3D<float> vin2)
		{
			v[0] = vin0;
			v[1] = vin1;
			v[2] = vin2;
		}

		void print()
		{
			Logger::printMsg("P1:", 1);
			v[0].print();
			Logger::printMsg("P2:", 1);
			v[1].print();
			Logger::printMsg("P3:", 1);
			v[2].print();
		}
	};
}