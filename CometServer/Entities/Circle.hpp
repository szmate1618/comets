#pragma once

#include "AbstractCollisionShape.hpp"
#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{

	class Circle: public AbstractCollisionShape
	{
	public:

		Circle() = delete;
		Circle(const geo::radian&, const geo::vector_2d&, const geo::real);
		virtual ~Circle() override;
		virtual bool InviteForCollision(geo::EmptyFrame, geo::EmptyFrame, AbstractCollisionShape&) override;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, AbstractTriangulatedPoly&) override;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, Circle&) override;
		virtual const geo::EmptyFrame& GetBoundingBox() override;
		virtual std::string GetName() override;
		const geo::real& GetRadius() const;

		const geo::real radius;

	private:

	};

}
