#include "TriangulatedPolyNaiveRotation.hpp"


namespace entity
{

	TriangulatedPolyNaiveRotation::TriangulatedPolyNaiveRotation
	(
		const geo::radian& orientation,
		const geo::vector_2d& position,
		const std::vector<geo::vector_2d>& vertices,
		const std::vector<uint16_t>& triangles
	) :
		AbstractTriangulatedPoly{ orientation, position, vertices, triangles }
	{
	}

	TriangulatedPolyNaiveRotation::~TriangulatedPolyNaiveRotation()
	{
	}

	geo::EmptyFrame TriangulatedPolyNaiveRotation::GetBoundingBox()
	{
		return { -10000, 10000, -10000, 10000 }; //TODO: Actually implement this.
	}

	void TriangulatedPolyNaiveRotation::SetOrientation(double radian)
	{
		//TODO: implement this.
	}

	std::string TriangulatedPolyNaiveRotation::GetName()
	{
		return "TriangulatedPolyNaiveRotation";
	}

}
