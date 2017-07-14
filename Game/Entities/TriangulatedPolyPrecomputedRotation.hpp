#ifndef SZM_TRIANGULATED_POLY_PRECOMPUTED_ROTATION
#define SZM_TRIANGULATED_POLY_PRECOMPUTED_ROTATION

#include "TriangulatedPoly.hpp"
#include "..\Geometry\Geometry.hpp"

#include <vector>


namespace entity
{

	class TriangulatedPolyPrecomputedRotation: public TriangulatedPoly
	{
	public:

		TriangulatedPolyPrecomputedRotation();
		TriangulatedPolyPrecomputedRotation(TriangulatedPoly&);
		~TriangulatedPolyPrecomputedRotation();
		void SetOrientation(double);
	    std::string GetName();

	private:

		static const int granularity = 3600;

		std::vector<geo::point_2d> rotated_vertices[granularity];
	};

}

#endif
