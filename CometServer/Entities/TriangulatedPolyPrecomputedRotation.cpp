#include "TriangulatedPolyPrecomputedRotation.hpp"


namespace entity
{

	TriangulatedPolyPrecomputedRotation::TriangulatedPolyPrecomputedRotation(const geo::degree& orientation, const geo::vector_2d& position, const std::vector<geo::vector_2d>& vertices) :
		AbstractTriangulatedPoly{ orientation, position, vertices }
	{
	}

	TriangulatedPolyPrecomputedRotation::~TriangulatedPolyPrecomputedRotation()
	{
	}

	const geo::EmptyFrame& TriangulatedPolyPrecomputedRotation::GetBoundingBox()
	{
		return { 0,0,0,0 }; //TODO: Actually implement this.
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
