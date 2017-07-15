#ifndef SZM_CIRCLE
#define SZM_CIRCLE

#include "CollisionShape.hpp"
#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{

	class Circle: public CollisionShape
	{
	public:

		Circle();
		Circle(geo::real);
		~Circle();
		bool InviteForCollision(geo::EmptyFrame, geo::EmptyFrame, CollisionShape&);
		bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, TriangulatedPoly&);
		bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, Circle&);
		std::string GetName();

		geo::real r;

	private:

	};

}

#endif
