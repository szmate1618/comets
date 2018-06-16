#include "TriangulatedPolyPrecomputedRotation.hpp"


namespace entity
{

	TriangulatedPolyPrecomputedRotation::TriangulatedPolyPrecomputedRotation()
	{

	}

	TriangulatedPolyPrecomputedRotation::TriangulatedPolyPrecomputedRotation(AbstractTriangulatedPoly& to)
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
