#include "AbstractTriangulatedPoly.hpp"
#include "Circle.hpp"


namespace entity 
{

	int AbstractTriangulatedPoly::arr[5000];

	AbstractTriangulatedPoly::AbstractTriangulatedPoly
	(
		const geo::radian& orientation,
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
			if (vertices[i].transformed(orientation, position).is_inside(myframe) &&
				vertices[i].transformed(orientation, position).is_inside(otherframe))
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
			geo::point_2d point_a = other.vertices.at(other.triangles.at(3 * i)).transformed(other.orientation, other.position);
			geo::point_2d point_b = other.vertices.at(other.triangles.at(3 * i + 1)).transformed(other.orientation, other.position);
			geo::point_2d point_c = other.vertices.at(other.triangles.at(3 * i + 2)).transformed(other.orientation, other.position);
			//TODO: This condition is too strict, think of a right angle triangle as a counter example.
			if (point_a.is_inside(otherframe) ||
				point_b.is_inside(otherframe) ||
				point_c.is_inside(otherframe))
			{
				arr[arr_counter] = i;
				arr_counter++;
			}
		}
		arr[arr_counter] = -1;

		if (arr[0] == -1 || arr[other_start] == -1) return false; //at least one of the frames is empty
	
		for (int i = other_start; arr[i] != -1; ++i)
		{
			geo::point_2d point_a = other.vertices.at(other.triangles.at(3 * arr[i])).transformed(other.orientation, other.position);
			geo::point_2d point_b = other.vertices.at(other.triangles.at(3 * arr[i] + 1)).transformed(other.orientation, other.position);
			geo::point_2d point_c = other.vertices.at(other.triangles.at(3 * arr[i] + 2)).transformed(other.orientation, other.position);
			geo::triangle other_face = { point_a, point_b, point_c };
			geo::EmptyFrame other_face_frame = other_face.as_frame();
			for (int j = 0; arr[j] != -1; ++j)
			{
				//TODO measure if this outer conditional is really neccesary
				if (vertices.at(arr[j]).transformed(orientation, position).is_inside(other_face_frame))
				{
					if (vertices.at(arr[j]).transformed(orientation, position).is_inside(other_face))
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
		for (const geo::point_2d& vertex : vertices)
		{
			geo::point_2d point = vertex.transformed(orientation, position);
			//TODO: Handle frames.
			if (point.is_inside(myframe) && (point - that.GetPosition()).length() <= that.GetRadius()) return true;
		}
		return false;
	}

}
