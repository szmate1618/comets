#ifndef SZM_TESSELLATED_OBJECT
#define SZM_TESSELLATED_OBJECT

#include "..\Geometry\Geometry.hpp"
#include "Engine.hpp"

#include <vector>
#include <string>


class Engine;

class TessellatedObject
{
public:

	friend class Engine;
	friend class InertialEngine;
	friend class AntiInertialEngine;
	friend class ParaInertialEngine;

	TessellatedObject();
	TessellatedObject(std::string);
	~TessellatedObject();
	bool CollideInto(geo::Frame<TessellatedObject>,
					geo::Frame<TessellatedObject>,
					TessellatedObject&);
	double GetOrientation();
	double SetOrientation(double radian);
					
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

#endif