#ifndef SZM_SHAPE
#define SZM_SHAPE

#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{
	class TessellatedObject;

	//With its derived classes, it implements a Visitor for double dispatch, so that the correct 
	//collision detection function is called for the dynamic types of the two involved shapes.
	class Shape
	{
	public:

		Shape();
		virtual ~Shape();
		virtual bool InviteForCollision(geo::EmptyFrame, geo::EmptyFrame, Shape&) = 0;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, TessellatedObject&) = 0;
		virtual std::string GetName() = 0; //Useful for debugging.

	private:

	};

}

#endif