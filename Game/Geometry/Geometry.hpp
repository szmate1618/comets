#ifndef SZM_GEOMETRY
#define SZM_GEOMETRY

/*#define FLOAT double
#define EPSILON 0.0005*/

#include <math.h>

namespace geo
{

	typedef double real;
	const real epsilon = 0.0005;

	struct point_2d{real x; real y;};

	typedef point_2d vector_2d;

	struct triangle{point_2d a; point_2d b; point_2d c;};
	
	struct EmptyFrame
	{
		real minx, maxx, miny, maxy;
	};

	template <class T>
	struct Frame: public EmptyFrame
	{
		T* entity;
	};
	
	bool equals(point_2d, point_2d, real);
	
	bool equals(point_2d, point_2d);

	point_2d sub(point_2d, point_2d);

	point_2d add(point_2d, point_2d);

	point_2d mul(point_2d, real);

	double length_cross(point_2d, point_2d);

	double dot_product(point_2d, point_2d);
	
	bool is_inside(point_2d, point_2d, point_2d, point_2d);

	bool is_inside(triangle, point_2d);

	bool is_inside(EmptyFrame, point_2d);

	double tri_minx(triangle);

	double tri_maxx(triangle);

	double tri_miny(triangle);

	double tri_maxy(triangle);

	point_2d point_2d_rotated(point_2d, double);

	EmptyFrame tri_as_frame(point_2d, point_2d, point_2d);

	bool mofo();
}

#endif