#include "TriangulatedPolyPrecomputedRotation.hpp"


namespace entity
{

	TriangulatedPolyPrecomputedRotation::TriangulatedPolyPrecomputedRotation
	(
		const geo::radian& orientation,
		const geo::vector_2d& position,
		const std::vector<geo::vector_2d>& vertices,
		const std::vector<uint16_t>& triangles
	) :
		AbstractTriangulatedPoly{ orientation, position, vertices, triangles }
	{
	}

	TriangulatedPolyPrecomputedRotation::~TriangulatedPolyPrecomputedRotation()
	{
	}

	geo::EmptyFrame TriangulatedPolyPrecomputedRotation::GetBoundingBox()
	{
		return { -10000, 10000, -10000, 10000 }; //TODO: Actually implement this.
	}

	void TriangulatedPolyPrecomputedRotation::SetOrientation(double radian)
	{
		//TODO: implement this.
	}

	std::string TriangulatedPolyPrecomputedRotation::GetName()
	{
		return "TriangulatedPolyPrecomputedRotation";
	}

}
