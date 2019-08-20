#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Geometry\Geometry.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{		

	TEST_CLASS(TestGeometry)
	{
	public:

		TEST_METHOD(AngleLiterals)
		{
			using namespace geo_literals;

			Assert::AreEqual(-1, -1.0_rad, 0.0, L"Radian literal error.");
			Assert::AreEqual(-0.5, -0.5_rad, 0.0, L"Radian literal error.");
			Assert::AreEqual(-0, -0.0_rad, 0.0, L"Radian literal error");
			Assert::AreEqual(1, 1.0_rad, 0.0, L"Radian literal error.");
			Assert::AreEqual(2, 2.0_rad, 0.0, L"Radian literal error.");
			Assert::AreEqual(3, 3.0_rad, 0.0, L"Radian literal error.");
			Assert::AreEqual(4, 4.0_rad, 0.0, L"Radian literal error.");
			Assert::AreEqual(7, 7.0_rad, 0.0, L"Radian literal error.");

			Assert::AreEqual(0, 0.0_deg, 0.0, L"Degree literal error.");
			Assert::AreEqual(2 * geo::PI, 360.0_deg, geo::epsilon, L"Degree literal error.");
			Assert::AreEqual(geo::PI, 180.0_deg, geo::epsilon, L"Degree literal error.");
			Assert::AreEqual(geo::PI / 2, 90.0_deg, geo::epsilon, L"Degree literal error.");
			Assert::AreEqual(geo::PI / 4, 45.0_deg, geo::epsilon, L"Degree literal error.");
			Assert::AreEqual(-3 * geo::PI / 4, -135.0_deg, geo::epsilon, L"Degree literal error.");
			Assert::AreEqual(2 * geo::PI, 360_deg, geo::epsilon, L"Degree literal error.");
			Assert::AreEqual(geo::PI, 180_deg, geo::epsilon, L"Degree literal error.");
			Assert::AreEqual(geo::PI / 2, 90_deg, geo::epsilon, L"Degree literal error.");
			Assert::AreEqual(geo::PI / 4, 45_deg, geo::epsilon, L"Degree literal error.");
			Assert::AreEqual(-3 * geo::PI / 4, -135_deg, geo::epsilon, L"Degree literal error.");
		}

		TEST_METHOD(AdditionSubtraction)
		{
			geo::point_2d O = {0, 0};
			geo::point_2d p1 = {1.23456789, 1.23456789};
			geo::point_2d p2 = {-1.23456789, -1.23456789};
			geo::point_2d p3 = {6.66, 6.66};
			Assert::IsTrue(O == p1 - p1, L"Subtracting element from itself failed.");
			Assert::IsTrue(p2.equals(O - p1, geo::epsilon), L"Constructing inverse element by subtraction failed.");
			Assert::IsTrue(O.equals(p1 + p2, geo::epsilon), L"Adding inverse element failed.");
			Assert::IsTrue(p1.equals((p1 + p3) - p3, geo::epsilon), L"Addition and subtractions should be the inverses of each other.");
		}
				
		TEST_METHOD(Mul)
		{
			geo::point_2d O = {0, 0};
			geo::point_2d p1 = {1.23456789, 1.23456789};
			Assert::IsTrue(p1 == p1 * 1, L"Identity transformation failed.");
			Assert::IsTrue(O == p1 * 0, L"Singular transformation failed.");
			Assert::IsTrue(O.equals(p1 + p1 * (-1), geo::epsilon), L"Inverting failed.");
		}
			
		TEST_METHOD(Rotation)
		{
			//NOTE: The name `_1` is not standard compliant.
			//Names starting with underscore are reserved for internals.
			geo::point_2d O = {0, 0};
			geo::point_2d _1 = {1, 0};
			geo::point_2d i = {0, 1};
			geo::point_2d p1 = {1.23456789, 1.23456789};
			Assert::IsTrue(p1.equals(p1.rotated(geo::PI * 2), geo::epsilon), L"Identity transformation failed.");
			Assert::IsTrue(O.equals(p1 + p1.rotated(geo::PI), geo::epsilon), L"Inverting failed.");
			Assert::AreEqual(0.0, p1.dot_product(p1.rotated(geo::PI / 2)), geo::epsilon, L"90° rotation of origo failed.");
			Assert::AreEqual(0.0, p1 * p1.rotated(- geo::PI / 2), geo::epsilon, L"-90° rotation of origo failed.");
			Assert::IsTrue(i.equals(_1.rotated(geo::PI / 2), geo::epsilon), L"90° rotation failed.");
			Assert::IsTrue(_1.equals(i.rotated(-geo::PI / 2), geo::epsilon), L"-90° rotation failed.");
			geo::point_2d rotated_p1 = p1.rotated(123);
			p1.rotate(123);
			Assert::IsTrue(rotated_p1.equals(p1, geo::epsilon), L"Mutable and immutable rotations provide different results.");
		}
			
		TEST_METHOD(TriangleBounds)
		{
			geo::point_2d a = {0, 0};
			geo::point_2d b = {2, -1};
			geo::point_2d c = {1, 1};
			geo::triangle t = {a, b, c};
			Assert::AreEqual(0.0, t.minx(), L"Failed to find minimal x coordinate of triangle.");
			Assert::AreEqual(2.0, t.maxx(), L"Failed to find maximal x coordinate of triangle.");
			Assert::AreEqual(-1.0, t.miny(), L"Failed to find minimal y coordinate of triangle.");
			Assert::AreEqual(1.0, t.maxy(), L"Failed to find maximal y coordinate of triangle.");

			geo::EmptyFrame f = geo::tri_as_frame(a, b, c);
			Assert::AreEqual(0.0, f.minx, L"Failed to find minimal x coordinate of frame.");
			Assert::AreEqual(2.0, f.maxx, L"Failed to find maximal x coordinate of frame.");
			Assert::AreEqual(-1.0, f.miny, L"Failed to find minimal y coordinate of frame.");
			Assert::AreEqual(1.0, f.maxy, L"Failed to find maximal y coordinate of frame.");
		}
			
		TEST_METHOD(InfinitesimalTriangleBounds)
		{
			geo::point_2d a = {0, 0};
			geo::triangle t = {a, a, a};
			Assert::AreEqual(0.0, t.minx(), L"Failed to find minimal x coordinate of infinitesimal triangle.");
			Assert::AreEqual(0.0, t.maxx(), L"Failed to find maximal x coordinate of infinitesimal triangle.");
			Assert::AreEqual(0.0, t.miny(), L"Failed to find minimal y coordinate of infinitesimal triangle.");
			Assert::AreEqual(0.0, t.maxy(), L"Failed to find maximal y coordinate of infinitesimal triangle.");

			geo::EmptyFrame f = geo::tri_as_frame(a, a, a);
			Assert::AreEqual(0.0, f.minx, L"Failed to find minimal x coordinate of infinitesimal frame.");
			Assert::AreEqual(0.0, f.maxx, L"Failed to find maximal x coordinate of infinitesimal frame.");
			Assert::AreEqual(0.0, f.miny, L"Failed to find minimal y coordinate of infinitesimal frame.");
			Assert::AreEqual(0.0, f.maxy, L"Failed to find maximal y coordinate of infinitesimal frame.");
		}

		TEST_METHOD(TriangleBoundsRandom)
		{
			srand(666);
			for (int i = 0; i < 15; i++)
			{
				geo::point_2d a = { static_cast<geo::real>(rand()), static_cast<geo::real>(rand()) };
				geo::point_2d b = { static_cast<geo::real>(rand()), static_cast<geo::real>(rand()) };
				geo::point_2d c = { static_cast<geo::real>(rand()), static_cast<geo::real>(rand()) };
				geo::real minx = __min(a.x, __min(b.x, c.x));
				geo::real maxx = __max(a.x, __max(b.x, c.x));
				geo::real miny = __min(a.y, __min(b.y, c.y));
				geo::real maxy = __max(a.y, __max(b.y, c.y));

				geo::triangle t = {a, b, c};
				Assert::AreEqual(minx, t.minx(), L"Failed to find minimal x coordinate of triangle.");
				Assert::AreEqual(maxx, t.maxx(), L"Failed to find maximal x coordinate of triangle.");
				Assert::AreEqual(miny, t.miny(), L"Failed to find minimal y coordinate of triangle.");
				Assert::AreEqual(maxy, t.maxy(), L"Failed to find maximal y coordinate of triangle.");

				geo::EmptyFrame f = geo::tri_as_frame(a, b, c);
				Assert::AreEqual(minx, f.minx, L"Failed to find minimal x coordinate of frame.");
				Assert::AreEqual(maxx, f.maxx, L"Failed to find maximal x coordinate of frame.");
				Assert::AreEqual(miny, f.miny, L"Failed to find minimal y coordinate of frame.");
				Assert::AreEqual(maxy, f.maxy, L"Failed to find maximal y coordinate of frame.");
			}
		}
		
        TEST_METHOD(InTriangleRandom)
        {
            srand(1337);

			geo::point_2d a = {0, 0};
			geo::point_2d b = {1, 0};
			geo::point_2d c = {0, 1};
			geo::triangle t  = {a, b, c};

            for (int i = 0; i < 20; i++)
            {
				geo::point_2d p = { static_cast<geo::real>(rand()), static_cast<geo::real>(rand()) };
				Assert::AreEqual(p.x + p.y <= 1, p.is_inside(t), L"Error with point inside or outside of triangle. Fuck C strings.");
            }
        }
		
        TEST_METHOD(InFrameRandom)
        {
            srand(1337);

			geo::EmptyFrame f = {0, 10, 0, 10};

            for (int i = 0; i < 10; i++)
            {
				geo::point_2d p = { static_cast<geo::real>(rand() % 11), static_cast<geo::real>(rand() % 11) };
				Assert::IsTrue(p.is_inside(f), L"Error with point inside of frame. Fuck C strings.");
            }
            for (int i = 0; i < 10; i++)
            {
				geo::point_2d p = {10.001 + static_cast<geo::real>(rand() % 11), 10.001 + static_cast<geo::real>(rand() % 11) };
				Assert::IsFalse(p.is_inside(f), L"Error with point outside of frame. Fuck C strings.");
            }
        }

        TEST_METHOD(VectorProducts)
        {
			//vector_2d is just and alias for point_2d
			geo::vector_2d v1 = {1, 0};
			geo::vector_2d v2 = {0, 1};
			Assert::AreEqual(0.0, v1 * v2, L"Dot product of perpendicular vectors should be zero.");

			geo::vector_2d v3 = {1, 4.5};
			geo::vector_2d v4 = {3.1, 1.2};
			Assert::AreEqual(8.5, v3 * v4, geo::epsilon, L"Dot product of these vectors should be 8.5.");
			Assert::AreEqual(-12.75, v3.length_cross(v4), geo::epsilon, L"Cross product of these vectors should be -12.75.");
			
			geo::vector_2d v5 = {1, 0};
			geo::vector_2d v6 = {1, 0};
			Assert::AreEqual(0.0, v5.length_cross(v6), L"Cross product of parallel vectors should be 0.");
		}
		
		TEST_METHOD(InHexagon)
		{
			geo::point_2d hexa[] = {{1, 0}, {0.5, 0.866}, {-0.5, 0.866}, {-1, 0}, {-0.5, -0.866}, {0.5, -0.866}};

			geo::point_2d p = {100, 100};
			bool in_convex_hexagon = p.is_inside_convex(hexa[0], hexa[1], hexa[2], hexa[3], hexa[4], hexa[5]);
			Assert::IsFalse(in_convex_hexagon, L"Problem with detecting point outside of convex hexagon.");

			p.x = hexa[1].x; p.y = hexa[1].y - 0.0001;
			in_convex_hexagon = p.is_inside_convex(hexa[0], hexa[1], hexa[2], hexa[3], hexa[4], hexa[5]);
			Assert::IsTrue(in_convex_hexagon, L"Problem with detecting point inside of 1st triangle slice.");

			p.x = hexa[2].x; p.y = hexa[2].y - 0.0001;
			in_convex_hexagon = p.is_inside_convex(hexa[0], hexa[1], hexa[2], hexa[3], hexa[4], hexa[5]);
			Assert::IsTrue(in_convex_hexagon, L"Problem with detecting point inside of 2nd triangle slice.");
			
			p.x = hexa[4].x; p.y = hexa[4].y + 0.0001;
			in_convex_hexagon = p.is_inside_convex(hexa[0], hexa[1], hexa[2], hexa[3], hexa[4], hexa[5]);
			Assert::IsTrue(in_convex_hexagon, L"Problem with detecting point inside of 3rd triangle slice.");
			
			p.x = hexa[5].x; p.y = hexa[5].y + 0.0001;
			in_convex_hexagon = p.is_inside_convex(hexa[0], hexa[1], hexa[2], hexa[3], hexa[4], hexa[5]);
			Assert::IsTrue(in_convex_hexagon, L"Problem with detecting point inside of 4th triangle slice.");
		}

		TEST_METHOD(InHexagonRandom)
		{
			srand(6);
			for (int i = 0; i < 20; i++)
			{
find_convex_hexa:
				geo::point_2d r = {1, 0};
				geo::point_2d convex_hexagon_attempt[6];
				for (int j = 0; j < 6; r.rotate(geo::PI / 3), j++)
				{
					geo::real length = static_cast<geo::real>(rand());
					convex_hexagon_attempt[j] = r * length;
				}

				for (int j = 0; j < 6 - 2; j++)
				{
					for (int k = j + 1; k < 6 - 1; k++)
					{
						for (int l = k + 1; l < 6; l++)
						{
							for (int m = 0; m < 6; m++)
							{
								if (m == j || m == k || m == l) continue;

								geo::triangle slice = {convex_hexagon_attempt[j], convex_hexagon_attempt[k], convex_hexagon_attempt[l]};
								if (convex_hexagon_attempt[m].is_inside(slice)) goto find_convex_hexa;
							}
						}
					}
				}
				
				geo::point_2d* hexa = convex_hexagon_attempt; //Hah! It's not just an attempt anymore!
				for (int j = 0; j < 1000; j++)
				{
					geo::point_2d p = { static_cast<geo::real>(rand()), static_cast<geo::real>(rand()) };
					bool in_a_triangle =
						p.is_inside(hexa[0], hexa[1], hexa[2]) || //Outcommenting this line doesn't do anything; this is strange.
						p.is_inside(hexa[0], hexa[2], hexa[3]) ||
						p.is_inside(hexa[0], hexa[3], hexa[4]) ||
						p.is_inside(hexa[0], hexa[4], hexa[5]);
					bool in_convex_hexagon = p.is_inside_convex(hexa[0], hexa[1], hexa[2], hexa[3], hexa[4], hexa[5]);
					Assert::AreEqual(in_a_triangle, in_convex_hexagon, L"There's something wrong here, sorry.");
				}
			}
		}

	};

}
