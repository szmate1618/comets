#ifndef SZM_TESSELLATED_OBJECT_NAIVE_ROTATION
#define SZM_TESSELLATED_OBJECT_NAIVE_ROTATION

#include "Shape.hpp"
#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{

	class TessellatedObjectNaiveRotation
	{
	public:

		TessellatedObjectNaiveRotation();
		TessellatedObjectNaiveRotation(TessellatedObject&); //TODO: do I really need this here? And in TessellatedObjectPrecomputedRotation?
		~TessellatedObjectNaiveRotation();
		void SetOrientation(double);
		std::string GetName();

	private:

	};

}

#endif