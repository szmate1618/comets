#include "Geometry.hpp"


namespace geo
{

	bool equals(point_2d v1, point_2d v2, real tolerance)
	{
		return abs(v1.x - v2.x) <= tolerance && abs(v1.y - v2.y) <= tolerance;
	}

	bool equals(point_2d v1, point_2d v2)
	{
		return equals(v1, v2, epsilon);
	}

	point_2d sub(point_2d v1, point_2d v2)
	{
		point_2d r;
		r.x = v1.x - v2.x;
		r.y = v1.y - v2.y;
		return r;
	}

	point_2d add(point_2d v1, point_2d v2)
	{
		point_2d r;
		r.x = v1.x + v2.x;
		r.y = v1.y + v2.y;
		return r;
	}

	point_2d mul(point_2d v, real s)
	{
		point_2d r;
		r.x = v.x * s;
		r.y = v.y * s;
		return r;
	}

	double length_cross(point_2d v1, point_2d v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	double dot_product(point_2d v1, point_2d v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	bool is_inside(point_2d a, point_2d b, point_2d c, point_2d p)
	{
		double sign1 = length_cross(sub(b, a), sub(p, a));
		double sign2 = length_cross(sub(c, b), sub(p, b));
		double sign3 = length_cross(sub(a, c), sub(p, c));
		// Isn't it a conditional? Maybe we should use bitwise operators.
		// Or keep them like this, and and use short-circuit and don't even calculate sign3 if not necessary.
		return (sign1 >= 0) && (sign2 >= 0) && (sign3 >= 0) || (sign1 <= 0) && (sign2 <= 0) && (sign3 <= 0); 
	}

	bool is_inside(triangle t, point_2d p)
	{
		//Can I trust MSVC to inline this? It doesn't need to be explicitlty asked to do it if the correct compiler flag is set.
		return is_inside(t.a, t.b, t.c, p);
	}

	bool is_inside(EmptyFrame f, point_2d p)
	{
		return (f.minx <= p.x && f.maxx >= p.x && f.miny <= p.y && f.maxy >= p.y);
	}

	bool is_inside_convex(point_2d a, point_2d b, point_2d c, point_2d d, point_2d e, point_2d f, point_2d p)
	{
		double sign1 = length_cross(sub(b, a), sub(p, a));
		double sign2 = length_cross(sub(c, b), sub(p, b));
		double sign3 = length_cross(sub(d, c), sub(p, c));
		double sign4 = length_cross(sub(e, d), sub(p, d));
		double sign5 = length_cross(sub(f, e), sub(p, e));
		double sign6 = length_cross(sub(a, f), sub(p, f));
		return (sign1 >= 0) && (sign2 >= 0) && (sign3 >= 0) && (sign4 >= 0) && (sign5 >= 0) && (sign6 >= 0)
			|| (sign1 <= 0) && (sign2 <= 0) && (sign3 <= 0) && (sign4 <= 0) && (sign5 <= 0) && (sign6 <= 0); 
	}

	//a<b b<c c<a 
	//1x0 4,6 a 0
	//01x 2,3 b 1
	//x01 1,5 c 2
	double tri_minx(triangle t)
	{
		if (t.a.x < t.b.x)
		{
			if (t.a.x < t.c.x) return t.a.x;
			else return t.c.x;
		}
		else
		{
			if (t.b.x < t.c.x) return t.b.x;
			else return t.c.x;
		}
	}

	double tri_maxx(triangle t)
	{
		if (t.a.x > t.b.x)
		{
			if (t.a.x > t.c.x) return t.a.x;
			else return t.c.x;
		}
		else
		{
			if (t.b.x > t.c.x) return t.b.x;
			else return t.c.x;
		}
	}

	double tri_miny(triangle t)
	{
		if (t.a.y < t.b.y)
		{
			if (t.a.y < t.c.y) return t.a.y;
			else return t.c.y;
		}
		else
		{
			if (t.b.y < t.c.y) return t.b.y;
			else return t.c.y;
		}
	}

	double tri_maxy(triangle t)
	{
		if (t.a.y > t.b.y)
		{
			if (t.a.y > t.c.y) return t.a.y;
			else return t.c.y;
		}
		else
		{
			if (t.b.y > t.c.y) return t.b.y;
			else return t.c.y;
		}
	}

	point_2d point_2d_rotated(point_2d p, double radian)
	{
		point_2d ret;
		ret.x = cos(radian) * p.x + sin(radian) * p.y;
		ret.y = -sin(radian) * p.x + cos(radian) * p.y;
		return ret;
	}

	void rotate_point_2d(point_2d& p, double radian)
	{
		real original_x = p.x; //Does this optimization actually do anything?
		p.x = cos(radian) * p.x + sin(radian) * p.y;
		p.y = -sin(radian) * original_x + cos(radian) * p.y;
	}

	EmptyFrame tri_as_frame(point_2d a, point_2d b, point_2d c)
	{
		EmptyFrame f;
		int acc_x = (a.x < b.x) << 2 | (b.x < c.x) << 1 | (c.x < a.x);
		switch(acc_x)
		{
		case 0: {f.minx = a.x; f.maxx = a.x; break;} //all equal, should not happen
		case 1: {f.minx = c.x; f.maxx = a.x; break;} //a >= b >= c and a > c
		case 2: {f.minx = b.x; f.maxx = c.x; break;} //c >= a >= b and c > b
		case 3: {f.minx = b.x; f.maxx = a.x; break;}
		case 4: {f.minx = a.x; f.maxx = b.x; break;}
		case 5: {f.minx = c.x; f.maxx = b.x; break;}
		case 6: {f.minx = a.x; f.maxx = c.x; break;}
		//case 7 is impossible
		}
		int acc_y = (a.y < b.y) << 2 | (b.y < c.y) << 1 | (c.y < a.y);
		switch(acc_y)
		{
		case 0: {f.miny = a.y; f.maxy = a.y; break;} //all equal, should not happen
		case 1: {f.miny = c.y; f.maxy = a.y; break;} //a >= b >= c and a > c
		case 2: {f.miny = b.y; f.maxy = c.y; break;} //c >= a >= b and c > b
		case 3: {f.miny = b.y; f.maxy = a.y; break;}
		case 4: {f.miny = a.y; f.maxy = b.y; break;}
		case 5: {f.miny = c.y; f.maxy = b.y; break;}
		case 6: {f.miny = a.y; f.maxy = c.y; break;}
		//case 7 is impossible
		}
		return f;
	}

	EmptyFrame tri_as_frame(triangle t)
	{
		return tri_as_frame(t.a, t.b, t.c);
	}

}
