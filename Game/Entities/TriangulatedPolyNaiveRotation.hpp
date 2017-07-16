#ifndef SZM_TRIANGULATED_POLY_NAIVE_ROTATION
#define SZM_TRIANGULATED_POLY_NAIVE_ROTATION

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
		virtual void SetOrientation(double) override;
		virtual std::string GetName() override;

	private:

	};

}

#endif
