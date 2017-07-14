#ifndef SZM_TRIANGULATED_POLY_NAIVE_ROTATION
#define SZM_TRIANGULATED_POLY_NAIVE_ROTATION

#include "CollisionShape.hpp"
#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{

	class TriangulatedPolyNaiveRotation
	{
	public:

		TriangulatedPolyNaiveRotation();
		TriangulatedPolyNaiveRotation(TriangulatedPoly&); //TODO: do I really need this here? And in TriangulatedPolyPrecomputedRotation?
		~TriangulatedPolyNaiveRotation();
		void SetOrientation(double);
		std::string GetName();

	private:

	};

}

#endif
