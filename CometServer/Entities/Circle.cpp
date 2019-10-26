#include "Circle.hpp"
#include "AbstractTriangulatedPoly.hpp"


namespace entity 
{

	Circle::Circle(const geo::radian& orientation, const geo::vector_2d& position, const geo::real radius) :
		AbstractCollisionShape{ orientation, position }, radius{ radius }
	{
	}

	Circle::~Circle()
	{
	}

	bool Circle::InviteForCollision(geo::EmptyFrame myframe, geo::EmptyFrame otherframe, AbstractCollisionShape& that)
	{
		return that.CollideInto(otherframe, myframe, *this); //Notice how we switched myframe and otherframe here.
	}

	bool Circle::CollideInto(geo::EmptyFrame myframe, geo::EmptyFrame otherframe, AbstractTriangulatedPoly& that)
	{
		//TODO: Investigate if circle collision checks need frames at all or not.
		//Probably not, because a circle should only be in 1 collision partition at once, since it doesn't have multiple vertices.
		//TODO: Remove friend class declaration in AbstractTriangulatedPoly, add public getters instead.
		for (size_t i = 0; i < that.triangles.size() / 3; ++i)
		{
			//TODO: By Unity convention, vertices are enumerated in a clockwise winding order.
			//Maybe this extra information could be used to speed up the collision check.
			geo::point_2d point_a = that.vertices.at(that.triangles.at(3 * i)).transformed(that.orientation, that.position);
			geo::point_2d point_b = that.vertices.at(that.triangles.at(3 * i + 1)).transformed(that.orientation, that.position);
			geo::point_2d point_c = that.vertices.at(that.triangles.at(3 * i + 2)).transformed(that.orientation, that.position);
			//TODO: This condition is too strict, think of a right angle triangle as a counter example.
			if ((this->position - point_a).length() <= this->radius ||
				(this->position - point_b).length() <= this->radius ||
				(this->position - point_c).length() <= this->radius ||
				this->position.is_inside_convex(geo::triangle{point_a, point_b, point_c}.as_hexagon(this->radius)))
			{
				return true;
			}
		}

		return false;
	}
	
	bool Circle::CollideInto(geo::EmptyFrame myframe, geo::EmptyFrame otherframe, Circle& that)
	{
		//TODO: Handle frames.
		return (this->position - that.position).length() <= this->radius + that.radius;
	}
	
	geo::EmptyFrame Circle::GetBoundingBox()
	{
		return { -10000, 10000, -10000, 10000 }; //TODO: Actually implement this.
	}

	std::string Circle::GetName()
	{
		return "Circle";
	}

	const geo::real& Circle::GetRadius() const
	{
		return radius;
	}

}
