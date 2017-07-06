#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Geometry\Geometry.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const double Pi = 3.14159265358979323846;

namespace Test
{		
	TEST_CLASS(TestGeometry)
	{
	public:
		
		TEST_METHOD(TestAdditionSubtraction)
		{
			geo::point_2d O = {0, 0};
			geo::point_2d p1 = {1.23456789, 1.23456789};
			geo::point_2d p2 = {-1.23456789, -1.23456789};
			geo::point_2d p3 = {6.66, 6.66};
			Assert::IsTrue(geo::equals(O, geo::sub(p1, p1)), L"Subtracting element from itself failed.");
			Assert::IsTrue(geo::equals(p2, geo::sub(O, p1)), L"Constructing inverse element by subtraction failed.");
			Assert::IsTrue(geo::equals(O, geo::add(p1, p2)), L"Adding inverse element failed.");
			Assert::IsTrue(geo::equals(p1, geo::sub(geo::add(p1, p3), p3)), L"Addition and subtractions should be the inverses of each other.");
		}
				
		TEST_METHOD(TestMul)
		{
			geo::point_2d O = {0, 0};
			geo::point_2d p1 = {1.23456789, 1.23456789};
			Assert::IsTrue(geo::equals(p1, geo::mul(p1, 1)), L"Identity transformation failed.");
			Assert::IsTrue(geo::equals(O, geo::mul(p1, 0)), L"Singular transformation failed.");
			Assert::IsTrue(geo::equals(O, geo::add(p1, geo::mul(p1, -1))), L"Inverting failed.");
		}
			
		TEST_METHOD(TestRotation)
		{
			geo::point_2d O = {0, 0};
			geo::point_2d p1 = {1.23456789, 1.23456789};
			Assert::IsTrue(geo::equals(p1, geo::point_2d_rotated(p1, Pi * 2)), L"Identity transformation failed.");
			Assert::IsTrue(geo::equals(O, geo::add(p1, geo::point_2d_rotated(p1, Pi))), L"Inverting failed.");
			Assert::AreEqual(0.0, geo::dot_product(p1, geo::point_2d_rotated(p1, Pi / 2)), geo::epsilon, L"90� rotation failed.");
			Assert::AreEqual(0.0, geo::dot_product(p1, geo::point_2d_rotated(p1, - Pi / 2)), geo::epsilon, L"-90� rotation failed.");
		}
			
		TEST_METHOD(TestTriangleBounds)
		{
			geo::point_2d a = {0, 0};
			geo::point_2d b = {2, -1};
			geo::point_2d c = {1, 1};
			geo::triangle t = {a, b, c};
			Assert::AreEqual(0.0, geo::tri_minx(t), L"Failed to find minimal x coordinate of triangle.");
			Assert::AreEqual(2.0, geo::tri_maxx(t), L"Failed to find maximal x coordinate of triangle.");
			Assert::AreEqual(-1.0, geo::tri_miny(t), L"Failed to find minimal y coordinate of triangle.");
			Assert::AreEqual(1.0, geo::tri_maxy(t), L"Failed to find maximal y coordinate of triangle.");

			geo::EmptyFrame f = geo::tri_as_frame(a, b, c);
			Assert::AreEqual(0.0, f.minx, L"Failed to find minimal x coordinate of frame.");
			Assert::AreEqual(2.0, f.maxx, L"Failed to find maximal x coordinate of frame.");
			Assert::AreEqual(-1.0, f.miny, L"Failed to find minimal y coordinate of frame.");
			Assert::AreEqual(1.0, f.maxy, L"Failed to find maximal y coordinate of frame.");
		}
			
		TEST_METHOD(TestInfinitesimalTriangleBounds)
		{
			geo::point_2d a = {0, 0};
			geo::triangle t = {a, a, a};
			Assert::AreEqual(0.0, geo::tri_minx(t), L"Failed to find minimal x coordinate of infinitesimal triangle.");
			Assert::AreEqual(0.0, geo::tri_maxx(t), L"Failed to find maximal x coordinate of infinitesimal triangle.");
			Assert::AreEqual(0.0, geo::tri_miny(t), L"Failed to find minimal y coordinate of infinitesimal triangle.");
			Assert::AreEqual(0.0, geo::tri_maxy(t), L"Failed to find maximal y coordinate of infinitesimal triangle.");

			geo::EmptyFrame f = geo::tri_as_frame(a, a, a);
			Assert::AreEqual(0.0, f.minx, L"Failed to find minimal x coordinate of infinitesimal frame.");
			Assert::AreEqual(0.0, f.maxx, L"Failed to find maximal x coordinate of infinitesimal frame.");
			Assert::AreEqual(0.0, f.miny, L"Failed to find minimal y coordinate of infinitesimal frame.");
			Assert::AreEqual(0.0, f.maxy, L"Failed to find maximal y coordinate of infinitesimal frame.");
		}

		TEST_METHOD(TestTriangleBoundsRandom)
		{
			srand(666);
			for (int i = 0; i < 15; i++)
			{
				geo::point_2d a = {rand(), rand()};
				geo::point_2d b = {rand(), rand()};
				geo::point_2d c = {rand(), rand()};
				geo::real minx = __min(a.x, __min(b.x, c.x));
				geo::real maxx = __max(a.x, __max(b.x, c.x));
				geo::real miny = __min(a.y, __min(b.y, c.y));
				geo::real maxy = __max(a.y, __max(b.y, c.y));

				geo::triangle t = {a, b, c};
				Assert::AreEqual(minx, geo::tri_minx(t), L"Failed to find minimal x coordinate of triangle.");
				Assert::AreEqual(maxx, geo::tri_maxx(t), L"Failed to find maximal x coordinate of triangle.");
				Assert::AreEqual(miny, geo::tri_miny(t), L"Failed to find minimal y coordinate of triangle.");
				Assert::AreEqual(maxy, geo::tri_maxy(t), L"Failed to find maximal y coordinate of triangle.");

				geo::EmptyFrame f = geo::tri_as_frame(a, b, c);
				Assert::AreEqual(minx, f.minx, L"Failed to find minimal x coordinate of frame.");
				Assert::AreEqual(maxx, f.maxx, L"Failed to find maximal x coordinate of frame.");
				Assert::AreEqual(miny, f.miny, L"Failed to find minimal y coordinate of frame.");
				Assert::AreEqual(maxy, f.maxy, L"Failed to find maximal y coordinate of frame.");
			}
		}
		
        TEST_METHOD(TestInTriangleRandom)
        {
            srand(1337);

			geo::point_2d a = {0, 0};
			geo::point_2d b = {1, 0};
			geo::point_2d c = {0, 1};
			geo::triangle t  = {a, b, c};

            for (int i = 0; i < 20; i++)
            {
				geo::point_2d p = {rand(), rand()};
				Assert::AreEqual(p.x + p.y <= 1, geo::is_inside(t, p), L"Error with point inside or outside of triangle. Fuck C strings.");
            }
        }
		
        TEST_METHOD(TestInFrameRandom)
        {
            srand(1337);

			geo::EmptyFrame f = {0, 10, 0, 10};

            for (int i = 0; i < 10; i++)
            {
				geo::point_2d p = {rand() % 11, rand() % 11};
				Assert::IsTrue(geo::is_inside(f, p), L"Error with point inside of frame. Fuck C strings.");
            }
            for (int i = 0; i < 10; i++)
            {
				geo::point_2d p = {10.001 + rand() % 11, 10.001 + rand() % 11};
				Assert::IsFalse(geo::is_inside(f, p), L"Error with point outside of frame. Fuck C strings.");
            }
        }

        TEST_METHOD(TestVectorProducts)
        {
			//vector_2d is just and alias for point_2d
			geo::vector_2d v1 = {1, 0};
			geo::vector_2d v2 = {0, 1};
			Assert::AreEqual(0.0, geo::dot_product(v1, v2), L"Dot product of perpendicular vectors should be zero.");

			geo::vector_2d v3 = {1, 4.5};
			geo::vector_2d v4 = {3.1, 1.2};
			Assert::AreEqual(8.5, geo::dot_product(v3, v4), geo::epsilon, L"Dot product of these vectors should be 8.5.");
			Assert::AreEqual(-12.75, geo::length_cross(v3, v4), geo::epsilon, L"Cross product of these vectors should be -12.75.");
			
			geo::vector_2d v5 = {1, 0};
			geo::vector_2d v6 = {1, 0};
			Assert::AreEqual(0.0, geo::length_cross(v5, v6), L"Cross product of parallel vectors should be 0.");
		}


	};
}