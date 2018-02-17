#pragma once

#include <cmath>


namespace geo_literals
{
	constexpr long double operator"" _deg(unsigned long long deg) { return deg / 180.0 * 3.14159265358979323846; } //TODO: geo::PI should be used here, somehow.

	constexpr long double operator"" _deg(long double deg) { return deg / 180.0 * 3.14159265358979323846; } //TODO: Same as above.

	constexpr long double operator"" _rad(long double rad) { return rad; } //TODO: Add _pi_rad literal.
}

namespace geo
{

	static constexpr double PI = 3.14159265358979323846; //TODO: Is it any better than using the pi contstant declared in cmath?

	using degree = double;

	using real = double; //TODO: This could be a template variable.
	constexpr real epsilon = 0.0005;

	struct point_2d { real x; real y; };

	using vector_2d = point_2d;

	struct triangle { point_2d a; point_2d b; point_2d c; };
	
	struct EmptyFrame
	{
		real minx, maxx, miny, maxy;
	};

	template <class T>
	struct Frame: public EmptyFrame
	{
		T* entity;
	};
	
	bool equals(point_2d, point_2d, real); //TODO: Pass everything by reference.
	
	bool equals(point_2d, point_2d);

	point_2d sub(point_2d, point_2d);

	point_2d add(point_2d, point_2d);

	point_2d mul(point_2d, real); //TODO: Actually this is a vector operation.

	double length_cross(point_2d, point_2d);

	double dot_product(point_2d, point_2d);
	
	bool is_inside(point_2d, point_2d, point_2d, point_2d);

	bool is_inside(triangle, point_2d);

	bool is_inside(EmptyFrame, point_2d);

	bool is_inside_convex(point_2d, point_2d, point_2d, point_2d, point_2d, point_2d, point_2d);

	double tri_minx(triangle);

	double tri_maxx(triangle);

	double tri_miny(triangle);

	double tri_maxy(triangle);

	point_2d point_2d_rotated(point_2d, degree);

	void rotate_point_2d(point_2d&, degree);

	EmptyFrame tri_as_frame(point_2d, point_2d, point_2d);

	EmptyFrame tri_as_frame(triangle);

	EmptyFrame add(EmptyFrame, vector_2d);

}
