#include "Circle.hpp"


namespace entity 
{

	Circle::Circle(const geo::degree& orientation, const geo::vector_2d& position, const geo::real radius) :
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
		return false;
		//TODO: implement this.
	}
	
	bool Circle::CollideInto(geo::EmptyFrame myframe, geo::EmptyFrame otherframe, Circle& that)
	{
		return geo::length(geo::sub(this->position, that.position)) <= this->radius + that.radius;
	}
	
	const geo::EmptyFrame& Circle::GetBoundingBox()
	{
		return { 0,0,0,0 }; //TODO: Actually implement this.
	}

	std::string Circle::GetName()
	{
		return "Circle";
	}

}
