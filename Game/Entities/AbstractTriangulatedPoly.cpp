#include "AbstractTriangulatedPoly.hpp"


namespace entity 
{

	int AbstractTriangulatedPoly::arr[5000];

	AbstractTriangulatedPoly::AbstractTriangulatedPoly()
	{
	}

	AbstractTriangulatedPoly::AbstractTriangulatedPoly(std::string)
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
		int arr_counter = 0;
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
		for(const trianlge_tile& t : other.faces)
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
		}

		return false;
	}

	bool AbstractTriangulatedPoly::CollideInto(geo::EmptyFrame myframe, geo::EmptyFrame otherframe, Circle& that)
	{
		return false;
		//TODO: implement this.
	}

}
