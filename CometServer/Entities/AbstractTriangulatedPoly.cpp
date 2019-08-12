#include "AbstractTriangulatedPoly.hpp"
#include "Circle.hpp"


namespace entity 
{

	//int AbstractTriangulatedPoly::arr[5000];

	AbstractTriangulatedPoly::AbstractTriangulatedPoly(const geo::degree& orientation, const geo::vector_2d& position, const std::vector<geo::vector_2d>& vertices) :
		AbstractCollisionShape{ orientation, position }, vertices{ vertices }
	{
	}

	AbstractTriangulatedPoly::~AbstractTriangulatedPoly()
	{
	}

	bool AbstractTriangulatedPoly::InviteForCollision(geo::EmptyFrame myframe, geo::EmptyFrame otherframe, AbstractCollisionShape& that)
	{
		return that.CollideInto(otherframe, myframe, *this); //Notice how we switched myframe and otherframe here.
	}

	bool AbstractTriangulatedPoly::CollideInto(geo::EmptyFrame myframe, geo::EmptyFrame otherframe, AbstractTriangulatedPoly& other)
	{
		//TODO: Make this work.
		/*int arr_counter = 0;
		for(const int& i: hull)
		{
			if (geo::is_inside(myframe, vertices[i]))
			{
				arr[arr_counter] = i;
				arr_counter++;
			}
		}
		arr[arr_counter] = -1;
		arr_counter++;
		int other_start = arr_counter;
		int j = 0;
		for(const trianlge_tile& t: other.faces)
		{
			if (geo::is_inside(otherframe, other.vertices[t.a])
				|| geo::is_inside(otherframe, other.vertices[t.b])
				|| geo::is_inside(otherframe, other.vertices[t.c]))
			{
				arr[arr_counter] = j;
				arr_counter++;
			}
			j++;
		}
		arr[arr_counter] = -1;

		if (arr[0] == -1 || arr[other_start] == -1) return false; //at least one of the frames is empty
	
		for (j = other_start; arr[j] != -1; j++) //TODO declare j here
		{
			geo::triangle other_face = { other.vertices[other.faces[j].a], other.vertices[other.faces[j].b], other.vertices[other.faces[j].c] };
			geo::EmptyFrame other_face_frame = geo::tri_as_frame(other_face);
			for (int i = 0; arr[i] != -1; i++)
			{
				//TODO measure if this outer conditional is really neccesary
				if (geo::is_inside(other_face_frame, vertices[i]))
				{
					if (geo::is_inside(other_face, vertices[i]))
					{
						return true;
					}
				}
			}
		}*/

		return false;
	}

	bool AbstractTriangulatedPoly::CollideInto(geo::EmptyFrame myframe, geo::EmptyFrame otherframe, Circle& that)
	{
		for (size_t i = 0; i < vertices.size(); ++i)
		{
			geo::point_2d point = geo::add(geo::point_2d_rotated(vertices.at(i), orientation), position);
			//TODO: Handle frames.
			if (/*geo::is_inside(myframe, point) && */geo::length(geo::sub(point, that.GetPosition())) <= that.GetRadius()) return true;
		}
		return false;
	}

}
