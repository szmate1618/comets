#include "TriangulatedPolyNaiveRotation.hpp"


namespace entity
{

	TriangulatedPolyNaiveRotation::TriangulatedPolyNaiveRotation(const geo::degree& orientation, const geo::vector_2d& position, const std::vector<geo::vector_2d>& vertices) :
		AbstractTriangulatedPoly{ orientation, position, vertices }
	{
	}

	TriangulatedPolyNaiveRotation::~TriangulatedPolyNaiveRotation()
	{
	}

	const geo::EmptyFrame& TriangulatedPolyNaiveRotation::GetBoundingBox()
	{
		return { 10000, 10000, 10000, 10000 }; //TODO: Actually implement this.
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
