#ifndef SZM_SHAPE
#define SZM_SHAPE

#include "..\Geometry\Geometry.hpp"

#include <string>


namespace entity
{

	class Shape
	{
	public:

		Shape();
		virtual ~Shape();
		bool InviteForCollision(geo::EmptyFrame, geo::EmptyFrame, Shape&); //Maybe make this final or whatever it's called when you disable overriding.
		virtual bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, Shape&) = 0;
		virtual std::string GetName() = 0; //Useful for debugging.

	private:

	};

}

#endif