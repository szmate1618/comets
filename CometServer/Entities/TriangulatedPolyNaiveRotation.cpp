#include "TriangulatedPolyNaiveRotation.hpp"


namespace entity
{

	TriangulatedPolyNaiveRotation::TriangulatedPolyNaiveRotation()
	{

	}

	TriangulatedPolyNaiveRotation::TriangulatedPolyNaiveRotation(AbstractTriangulatedPoly& to)
	{
	}

	TriangulatedPolyNaiveRotation::~TriangulatedPolyNaiveRotation()
	{
	}

	const geo::EmptyFrame& TriangulatedPolyNaiveRotation::GetBoundingBox()
	{
		return { 0,0,0,0 }; //TODO: Actually implement this.
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
