#pragma once

#include "AbstractTriangulatedPoly.hpp"
#include "..\Geometry\Geometry.hpp"

#include <vector>


namespace entity
{

	class TriangulatedPolyPrecomputedRotation: public AbstractTriangulatedPoly
	{
	public:

		TriangulatedPolyPrecomputedRotation();
		TriangulatedPolyPrecomputedRotation(AbstractTriangulatedPoly&);
		virtual ~TriangulatedPolyPrecomputedRotation() override;
		virtual const geo::EmptyFrame& GetBoundingBox() override;
		virtual void SetOrientation(double) override;
	    virtual std::string GetName() override;

	private:

		static const int granularity = 3600;

		std::vector<geo::point_2d> rotated_vertices[granularity]; //TODO: Find out why I am mixing normal arrays with vectors.
	};

}
