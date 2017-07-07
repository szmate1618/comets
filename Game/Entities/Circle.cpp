#include "Circle.hpp"


namespace entity 
{

	Circle::Circle()
	{
	}

	Circle::~Circle()
	{
	}

	bool Circle::InviteForCollision(geo::EmptyFrame myframe, geo::EmptyFrame otherframe, CollisionShape& that)
	{
		return that.CollideInto(otherframe, myframe, *this); //Notice how we switched myframe and otherframe here.
	}

	bool Circle::CollideInto(geo::EmptyFrame myframe, geo::EmptyFrame otherframe, TriangulatedPoly& that)
	{
		//TODO: implement this.
	}
	
	bool Circle::CollideInto(geo::EmptyFrame myframe, geo::EmptyFrame otherframe, Circle& that)
	{
		//TODO: implement this.
	}
	
	std::string Circle::GetName()
	{
		return "Circle";
	}

}