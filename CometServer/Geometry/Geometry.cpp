#include "Geometry.hpp"


namespace geo
{

	bool vector_2d::equals(const vector_2d& other, real tolerance) const
	{
		return std::abs(x - other.x) <= tolerance && std::abs(y - other.y) <= tolerance;
	}

	bool vector_2d::operator==(const vector_2d& other) const
	{
		return x == other.x && y == other.y;
	}

	real vector_2d::length() const
	{
		return std::sqrt(x * x + y * y);
	}

	vector_2d vector_2d::operator-(const vector_2d& other) const
	{
		vector_2d ret;
		ret.x = x - other.x;
		ret.y = y - other.y;
		return ret;
	}

	vector_2d vector_2d::operator+(const vector_2d& other) const
	{
		vector_2d ret;
		ret.x = x + other.x;
		ret.y = y + other.y;
		return ret;
	}

	vector_2d vector_2d::operator*(const real r) const
	{
		vector_2d ret;
		ret.x = x * r;
		ret.y = y * r;
		return ret;
	}

	vector_2d vector_2d::operator/(const real r) const
	{
		vector_2d ret;
		ret.x = x / r;
		ret.y = y / r;
		return ret;
	}

	real vector_2d::length_cross(const vector_2d& other) const
	{
		return x * other.y - y * other.x;
	}

	real vector_2d::dot_product(const vector_2d& other) const
	{
		return x * other.x + y * other.y;
	}

	real vector_2d::operator*(const vector_2d& other) const
	{
		return this->dot_product(other);
	}

	bool vector_2d::is_inside(const vector_2d& a, const vector_2d& b, const vector_2d& c) const
	{
		double sign2 = (c - b).length_cross(*this - b);
		double sign3 = (a - c).length_cross(*this - c);
		double sign1 = (b - a).length_cross(*this - a);
		//Isn't it a conditional? Maybe we should use bitwise operators.
		//Or keep them like this, and and use short-circuit and don't even calculate sign3 if not necessary.
		return (sign1 >= 0) && (sign2 >= 0) && (sign3 >= 0) || (sign1 <= 0) && (sign2 <= 0) && (sign3 <= 0); 
	}

	bool vector_2d::is_inside(const triangle& t) const
	{
		//Can I trust MSVC to inline this? It doesn't need to be explicitlty asked to do it if the correct compiler flag is set.
		//NOTE: My understanding of what the 'inline' keyword means and what it doesn't has improved since writing the above comment.
		//In short, the compiler inlines whatever it wants, it probably knows better than I do.
		return this->is_inside(t.a, t.b, t.c);
	}

	bool vector_2d::is_inside(const EmptyFrame& f) const
	{
		return (f.minx <= x && f.maxx >= x && f.miny <= y && f.maxy >= y);
	}

	bool vector_2d::is_inside_convex(const vector_2d& a, const vector_2d& b, const vector_2d& c, const vector_2d& d, const vector_2d& e, const vector_2d& f) const
	{
		double sign1 = (b - a).length_cross(*this - a);
		double sign2 = (c - b).length_cross(*this - b);
		double sign3 = (d - c).length_cross(*this - c);
		double sign4 = (e - d).length_cross(*this - d);
		double sign5 = (f - e).length_cross(*this - e);
		double sign6 = (a - f).length_cross(*this - f);
		return (sign1 >= 0) && (sign2 >= 0) && (sign3 >= 0) && (sign4 >= 0) && (sign5 >= 0) && (sign6 >= 0)
			|| (sign1 <= 0) && (sign2 <= 0) && (sign3 <= 0) && (sign4 <= 0) && (sign5 <= 0) && (sign6 <= 0); 
	}

	vector_2d vector_2d::rotated(const radian angle) const
	{
		vector_2d ret;
		ret.x = std::cos(angle) * x - std::sin(angle) * y;
		ret.y = std::sin(angle) * x + std::cos(angle) * y;
		return ret;
	}

	void vector_2d::rotate(const radian angle)
	{
		real original_x = x; //Does this optimization actually do anything?
		x = std::cos(angle) * x - std::sin(angle) * y;
		y = std::sin(angle) * original_x + std::cos(angle) * y;
	}

	vector_2d vector_2d::transformed(const radian angle, const vector_2d& center) const
	{
		return this->rotated(angle) + center;
	}

	//a<b b<c c<a 
	//1x0 4,6 a 0
	//01x 2,3 b 1
	//x01 1,5 c 2
	real triangle::minx() const
	{
		if (this->a.x < this->b.x)
		{
			if (this->a.x < this->c.x) return this->a.x;
			else return this->c.x;
		}
		else
		{
			if (this->b.x < this->c.x) return this->b.x;
			else return this->c.x;
		}
	}

	real triangle::maxx() const
	{
		if (this->a.x > this->b.x)
		{
			if (this->a.x > this->c.x) return this->a.x;
			else return this->c.x;
		}
		else
		{
			if (this->b.x > this->c.x) return this->b.x;
			else return this->c.x;
		}
	}

	real triangle::miny() const
	{
		if (this->a.y < this->b.y)
		{
			if (this->a.y < this->c.y) return this->a.y;
			else return this->c.y;
		}
		else
		{
			if (this->b.y < this->c.y) return this->b.y;
			else return this->c.y;
		}
	}

	real triangle::maxy() const
	{
		if (this->a.y > this->b.y)
		{
			if (this->a.y > this->c.y) return this->a.y;
			else return this->c.y;
		}
		else
		{
			if (this->b.y > this->c.y) return this->b.y;
			else return this->c.y;
		}
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

	EmptyFrame add(EmptyFrame f, vector_2d v)
	{
		return { f.minx + v.x, f.maxx + v.x, f.miny + v.y, f.maxy + v.y };
	}

}
