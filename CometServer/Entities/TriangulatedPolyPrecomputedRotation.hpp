#pragma once

#include "AbstractTriangulatedPoly.hpp"
#include "..\Geometry\Geometry.hpp"

#include <vector>


namespace entity
{

	class TriangulatedPolyPrecomputedRotation: public AbstractTriangulatedPoly
	{
	public:

		TriangulatedPolyPrecomputedRotation() = delete;
		TriangulatedPolyPrecomputedRotation(const geo::degree&, const geo::vector_2d&, const std::vector<geo::vector_2d>&, const std::vector<uint16_t>&);
		virtual ~TriangulatedPolyPrecomputedRotation() override;
		virtual const geo::EmptyFrame& GetBoundingBox() override;
		virtual void SetOrientation(double) override;
	    virtual std::string GetName() override;

	private:

		//TODO: Remove if not needed.
		static const int granularity = 3600;

		std::vector<geo::point_2d> rotated_vertices[granularity]; //TODO: Find out why I am mixing normal arrays with vectors.
	};

}
