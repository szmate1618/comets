#include "TessellatedObject.hpp"
//#include "QuadTree.hpp"

#include <fstream>


int TessellatedObject::arr[5000];

TessellatedObject::TessellatedObject()
{
}

TessellatedObject::TessellatedObject(std::string)
{
}

TessellatedObject::~TessellatedObject()
{
}

bool TessellatedObject::CollideInto(geo::Frame<TessellatedObject> myframe,
									geo::Frame<TessellatedObject> otherframe,
									TessellatedObject& other)
{
	int arr_counter = 0;
	for(int& i: hull)
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
	for(trianlge_tile& t: other.faces)
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

	for (int i = 0; arr[i] != -1; i++)
	{
		for (j = other_start; arr[j] != -1; j++) //TODO declare j here
		{
			//TODO measure if this outer conditional is really neccesary
			//One thing is for sure: we should move the tri_as_frame call outside of the loop, since it will be used multiple times.
			if (geo::is_inside(geo::tri_as_frame(other.vertices[other.faces[j].a], other.vertices[other.faces[j].b], other.vertices[other.faces[j].c]), vertices[i]))
			{
				return true;
			}
		}
	}

	return false;
}