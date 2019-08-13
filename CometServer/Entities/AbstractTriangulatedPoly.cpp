#include "AbstractTriangulatedPoly.hpp"
#include "Circle.hpp"


namespace entity 
{

	int AbstractTriangulatedPoly::arr[5000];

	AbstractTriangulatedPoly::AbstractTriangulatedPoly
	(
		const geo::degree& orientation,
		const geo::vector_2d& position,
		const std::vector<geo::vector_2d>& vertices,
		const std::vector<uint16_t>& triangles
	) :
		AbstractCollisionShape{ orientation, position }, vertices{ vertices }, triangles{ triangles }
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
		for (int i = 0; i < vertices.size(); ++i)
		{
			if (geo::is_inside(myframe, geo::add(geo::point_2d_rotated(vertices[i], orientation), position)) &&
				geo::is_inside(otherframe, geo::add(geo::point_2d_rotated(vertices[i], orientation), position)))
			{
				arr[arr_counter] = i;
				arr_counter++;
			}
		}
		arr[arr_counter] = -1; //TODO: Add checks for overindexing.
		arr_counter++;
		int other_start = arr_counter;
		for(int i = 0; i < other.triangles.size() / 3; ++i)
		{
			//TODO: By Unity convention, vertices are enumerated in a clockwise winding order.
			//Maybe this extra information could be used to speed up the collision check.
			geo::point_2d point_a = geo::add(geo::point_2d_rotated(other.vertices.at(other.triangles.at(3 * i)), other.orientation), other.position);
			geo::point_2d point_b = geo::add(geo::point_2d_rotated(other.vertices.at(other.triangles.at(3 * i + 1)), other.orientation), other.position);
			geo::point_2d point_c = geo::add(geo::point_2d_rotated(other.vertices.at(other.triangles.at(3 * i + 2)), other.orientation), other.position);
			//TODO: This condition is too strict, think of a right angle triangle as a counter example.
			if (geo::is_inside(otherframe, point_a)
				|| geo::is_inside(otherframe, point_b)
				|| geo::is_inside(otherframe, point_c))
			{
				arr[arr_counter] = i;
				arr_counter++;
			}
		}
		arr[arr_counter] = -1;

		if (arr[0] == -1 || arr[other_start] == -1) return false; //at least one of the frames is empty
	
		for (int i = other_start; arr[i] != -1; ++i)
		{
			geo::point_2d point_a = geo::add(geo::point_2d_rotated(other.vertices.at(other.triangles.at(3 * arr[i])), other.orientation), other.position);
			geo::point_2d point_b = geo::add(geo::point_2d_rotated(other.vertices.at(other.triangles.at(3 * arr[i] + 1)), other.orientation), other.position);
			geo::point_2d point_c = geo::add(geo::point_2d_rotated(other.vertices.at(other.triangles.at(3 * arr[i] + 2)), other.orientation), other.position);
			geo::triangle other_face = { point_a, point_b, point_c };
			geo::EmptyFrame other_face_frame = geo::tri_as_frame(other_face);
			for (int j = 0; arr[j] != -1; ++j)
			{
				//TODO measure if this outer conditional is really neccesary
				if (geo::is_inside(other_face_frame, geo::add(geo::point_2d_rotated(vertices.at(arr[j]), orientation), position)))
				{
					if (geo::is_inside(other_face, geo::add(geo::point_2d_rotated(vertices.at(arr[j]), orientation), position)))
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
		for (const geo::point_2d vertex : vertices)
		{
			geo::point_2d point = geo::add(geo::point_2d_rotated(vertex, orientation), position);
			//TODO: Handle frames.
			if (geo::is_inside(myframe, point) && geo::length(geo::sub(point, that.GetPosition())) <= that.GetRadius()) return true;
		}
		return false;
	}

}
