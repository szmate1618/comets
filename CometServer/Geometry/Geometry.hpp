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

	//Forward declarations.
	struct triangle;
	struct EmptyFrame;

	static constexpr double PI = 3.14159265358979323846; //TODO: Is it any better than using the pi contstant declared in cmath?

	using radian = double;

	using real = double; //TODO: This could be a template variable.
	constexpr real epsilon = 0.0005;

	struct vector_2d
	{
		real x;
		real y;

		bool equals(const vector_2d&, const real) const;
		bool operator==(const vector_2d&) const;
		real length() const;
		vector_2d operator-(const vector_2d&) const;
		vector_2d operator+(const vector_2d&) const;
		vector_2d operator*(const real) const;
		vector_2d operator/(const real) const;
		real length_cross(const vector_2d&) const;
		real dot_product(const vector_2d&) const;
		real operator*(const vector_2d&) const;
		bool is_inside(const vector_2d&, const vector_2d&, const vector_2d&) const;
		bool is_inside(const triangle&) const;
		bool is_inside(const EmptyFrame&) const;
		bool is_inside_convex(const vector_2d&, const vector_2d&, const vector_2d&, const vector_2d&, const vector_2d&, const vector_2d&) const;
		vector_2d rotated(const radian) const;
		void rotate(const radian);
		vector_2d transformed(const radian, const vector_2d& center) const;
	};

	using point_2d = vector_2d;

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

	real tri_minx(triangle);

	real tri_maxx(triangle);

	real tri_miny(triangle);

	real tri_maxy(triangle);

	EmptyFrame tri_as_frame(point_2d, point_2d, point_2d);

	EmptyFrame tri_as_frame(triangle);

	EmptyFrame add(EmptyFrame, vector_2d);

}
