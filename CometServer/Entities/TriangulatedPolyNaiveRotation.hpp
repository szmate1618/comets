#pragma once

#include "AbstractTriangulatedPoly.hpp"
#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{

	class TriangulatedPolyNaiveRotation: public AbstractTriangulatedPoly
	{
	public:

		TriangulatedPolyNaiveRotation();
		TriangulatedPolyNaiveRotation(AbstractTriangulatedPoly&); //TODO: do I really need this here? And in TriangulatedPolyPrecomputedRotation?
		virtual ~TriangulatedPolyNaiveRotation() override;
		virtual const geo::EmptyFrame& GetBoundingBox() override;
		virtual void SetOrientation(double) override;
		virtual std::string GetName() override;

	private:

	};

}
