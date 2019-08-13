#pragma once

#include "AbstractTriangulatedPoly.hpp"
#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{

	class TriangulatedPolyNaiveRotation: public AbstractTriangulatedPoly
	{
	public:

		TriangulatedPolyNaiveRotation() = delete;
		TriangulatedPolyNaiveRotation(const geo::degree&, const geo::vector_2d&, const std::vector<geo::vector_2d>&, const std::vector<uint16_t>&);
		virtual ~TriangulatedPolyNaiveRotation() override;
		virtual const geo::EmptyFrame& GetBoundingBox() override;
		virtual void SetOrientation(double) override;
		virtual std::string GetName() override;

	private:

	};

}
