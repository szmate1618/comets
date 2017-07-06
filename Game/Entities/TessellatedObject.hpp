#ifndef SZM_TESSELLATED_OBJECT
#define SZM_TESSELLATED_OBJECT

#include "Shape.hpp"
#include "..\Geometry\Geometry.hpp"

#include <vector>
#include <string>


namespace entity
{

	class TessellatedObject: public Shape
	{
	public:

		TessellatedObject();
		TessellatedObject(std::string); //TODO: figure out why I declared this.
		virtual ~TessellatedObject();
		bool InviteForCollision(geo::EmptyFrame, geo::EmptyFrame, Shape&);
		bool CollideInto(geo::EmptyFrame, geo::EmptyFrame, TessellatedObject&);
		virtual void SetOrientation(double radian) = 0;
					
	private:

		static int arr[];  //Some preallocated general purpose memory, here goes thread safety.
						   //Wouldn't a local be better, though?
		geo::real orientation;
		geo::point_2d pivot;
		geo::vector_2d velocity;
		geo::vector_2d acceleration;
	
		struct trianlge_tile
		{
			int a;
			int b;
			int c;
			int health;
		};
		std::vector<geo::point_2d> vertices;
		std::vector<int> hull;
		std::vector<trianlge_tile> faces;
	};

}

#endif