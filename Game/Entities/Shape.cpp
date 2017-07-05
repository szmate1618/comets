#include "Shape.hpp"


namespace entity 
{

	Shape::Shape()
	{
	}

	Shape::~Shape()
	{
	}

	bool Shape::InviteForCollision(geo::EmptyFrame myframe, geo::EmptyFrame otherframe,  Shape& that)
	{
		return that.CollideInto(otherframe, myframe, *this); //Notice how we switched myframe and otherframe here.
	}

}