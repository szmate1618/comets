#ifndef SZM_TRIANGULATED_POLY
#define SZM_TRIANGULATED_POLY

#include "CollisionShape.hpp"
#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{

	class Circle: public CollisionShape
	{
	public:

		Circle();
		~Circle();
		bool InviteForCollision(geo::EmptyFrame, geo::EmptyFrame, CollisionShape&);
		bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, TriangulatedPoly&);
		bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, Circle&);
		std::string GetName();
					
	private:

	};

}

#endif