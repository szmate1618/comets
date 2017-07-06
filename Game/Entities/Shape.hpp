#ifndef SZM_SHAPE
#define SZM_SHAPE

#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{
	class TessellatedObject;

	class Shape
	{
	public:

		Shape();
		virtual ~Shape();
		virtual bool InviteForCollision(geo::EmptyFrame, geo::EmptyFrame, Shape&) = 0;
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, TessellatedObject&) = 0;
		virtual std::string GetName() = 0; //Useful for debugging.

	private:

	};

}

#endif