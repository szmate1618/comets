#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Geometry\Geometry.hpp"
#include "..\Entities\TriangulatedPolyNaiveRotation.hpp"
#include "..\Entities\Circle.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{		

	TEST_CLASS(TestCollision)
	{
	private:

		std::vector<geo::vector_2d> vertices[2];
		std::vector<uint16_t> triangles[2];

	public:

		TEST_METHOD(PolyToPoly)
		{
		}

		TEST_METHOD(PolyToCircle)
		{
		}

		TEST_METHOD(CircleToCircle)
		{
			geo::radian orientation1;
			geo::radian orientation2;
			geo::point_2d position1{0,0};
			geo::point_2d position2{ 0,0 };
			geo::real radius1= 0;
			geo::real radius2= 0;

			entity::Circle circle1(orientation1, position1, radius1);
			entity::Circle circle2(orientation2, position2, radius2);

			for (geo::radian o1 : {0.0, geo::PI / 4.0, geo::PI / 3.0, geo::PI})
			{
				orientation1 = o1;
				for (geo::radian o2 : {0.0, -geo::PI / 4.0, -geo::PI / 3.0, geo::PI})
				{
					orientation1 = o2;
					Assert::AreEqual(
						(circle1.GetPosition() - circle2.GetPosition()).length() <= circle1.GetRadius() + circle2.GetRadius(),
						circle1.CollideInto({ -10000,10000,-10000,10000 }, { -10000,10000,-10000,10000 }, circle2)
					);
					Assert::AreEqual(
						(circle1.GetPosition() - circle2.GetPosition()).length() <= circle1.GetRadius() + circle2.GetRadius(),
						circle2.CollideInto({ -10000,10000,-10000,10000 }, { -10000,10000,-10000,10000 }, circle1)
					);
				}
			}
		}

		TEST_METHOD(CircleToPoly)
		{
		}

	};

}
