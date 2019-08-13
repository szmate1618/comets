#pragma once

#include "AbstractCollisionShape.hpp"
#include "..\Geometry\Geometry.hpp"

#include <vector>


namespace entity
{

	class AbstractTriangulatedPoly: public AbstractCollisionShape
	{
	public:

		AbstractTriangulatedPoly() = delete;
		AbstractTriangulatedPoly(const geo::degree&, const geo::vector_2d&, const std::vector<geo::vector_2d>&, const std::vector<uint16_t>&);
		virtual ~AbstractTriangulatedPoly() override;
		virtual bool InviteForCollision(geo::EmptyFrame, geo::EmptyFrame, AbstractCollisionShape&) override;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, AbstractTriangulatedPoly&) override;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, Circle&) override;
		virtual void SetOrientation(double radian) = 0;
					
	protected:

		const std::vector<geo::vector_2d>& vertices;
		const std::vector<uint16_t>& triangles;

		static int arr[];  //Some preallocated general purpose memory, here goes thread safety.
						   //Wouldn't a local be better, though?
		/*geo::real orientation;
		geo::point_2d pivot;
		geo::vector_2d velocity;
		geo::vector_2d acceleration;
	
		struct trianlge_tile
		{
			int a;
			int b;
			int c;
			int health;
		};
		std::vector<geo::point_2d> vertices;
		std::vector<int> hull;
		std::vector<trianlge_tile> faces;*/
	};

}
