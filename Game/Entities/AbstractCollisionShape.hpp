#pragma once

#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{
	class AbstractTriangulatedPoly;
	class Circle;

	//With its derived classes, it implements a Visitor for double dispatch, so that the correct 
	//collision detection function is called for the dynamic types of the two involved AbstractCollisionShapes.
	class AbstractCollisionShape
	{
	public:

		AbstractCollisionShape();
		virtual ~AbstractCollisionShape();
		virtual bool InviteForCollision(geo::EmptyFrame, geo::EmptyFrame, AbstractCollisionShape&) = 0;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, AbstractTriangulatedPoly&) = 0;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, Circle&) = 0;
		virtual std::string GetName() = 0; //Useful for debugging.

	private:

	};

}
