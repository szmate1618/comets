#ifndef SZM_COLLISION_SHAPE
#define SZM_COLLISION_SHAPE

#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{
	class TriangulatedPoly;
	class Circle;

	//With its derived classes, it implements a Visitor for double dispatch, so that the correct 
	//collision detection function is called for the dynamic types of the two involved CollisionShapes.
	class CollisionShape
	{
	public:

		CollisionShape();
		virtual ~CollisionShape();
		virtual bool InviteForCollision(geo::EmptyFrame, geo::EmptyFrame, CollisionShape&) = 0;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, TriangulatedPoly&) = 0;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, Circle&) = 0;
		virtual std::string GetName() = 0; //Useful for debugging.

	private:

	};

}

#endif
