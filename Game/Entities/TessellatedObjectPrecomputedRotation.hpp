#ifndef SZM_TESSELLATED_OBJECT_PRECOMPUTED_ROTATION
#define SZM_TESSELLATED_OBJECT_PRECOMPUTED_ROTATION

#include "TessellatedObject.hpp"
#include "..\Geometry\Geometry.hpp"

#include <vector>


class TessellatedObjectPrecomputedRotation: public TessellatedObject
{
public:

	TessellatedObjectPrecomputedRotation();
	TessellatedObjectPrecomputedRotation(TessellatedObject);
	~TessellatedObjectPrecomputedRotation();
	void SetRotation(geo::real);

private:

	static const int granularity = 3600;

	std::vector<geo::point_2d> rotated_vertices[granularity];
};

#endif