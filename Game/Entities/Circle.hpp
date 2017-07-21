#ifndef SZM_CIRCLE
#define SZM_CIRCLE

#include "AbstractCollisionShape.hpp"
#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{

	class Circle: public AbstractCollisionShape
	{
	public:

		Circle();
		Circle(geo::real);
		virtual ~Circle() override;
		virtual bool InviteForCollision(geo::EmptyFrame, geo::EmptyFrame, AbstractCollisionShape&) override;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, AbstractTriangulatedPoly&) override;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, Circle&) override;
		virtual std::string GetName() override;

		geo::real r;

	private:

	};

}

#endif
