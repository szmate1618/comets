#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Geometry\Geometry.hpp"
#include "..\Entities\TriangulatedPolyNaiveRotation.hpp"
#include "..\Entities\Circle.hpp"

#include <filesystem>
#include <fstream>
#include <cassert>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(TestCollisionScenarios)
	{
	private:

		bool one_collides_into_two;
		bool two_collides_into_one;

		struct CollisionTestEntity
		{
			geo::real orientation;
			geo::vector_2d position;
			std::vector<geo::vector_2d> collision_vertices;
			std::vector<uint16_t> triangles;
		};

		CollisionTestEntity entity1;
		CollisionTestEntity entity2;

		void ReadEntity(std::ifstream& scenario, CollisionTestEntity& entity)
		{
			scenario >> entity.orientation;
			scenario >> entity.position.x;
			scenario >> entity.position.y;

			size_t vertex_count;
			size_t triangle_count;
			scenario >> vertex_count >> triangle_count; //NOTE: This allows both space and newline separators.
			entity.collision_vertices.resize(vertex_count);
			entity.triangles.resize(triangle_count * 3);

			std::string dummy_line;

			for (size_t i = 0; i < vertex_count; i++)
			{
				scenario >> entity.collision_vertices[i].x;
				scenario >> entity.collision_vertices[i].y;
			}
			for (size_t i = 0; i < vertex_count * 2; i++) scenario >> dummy_line;
			for (size_t i = 0; i < triangle_count * 3; i++)
			{
				scenario >> entity.triangles[i];
			}
		}

		void ReadScenario(std::ifstream& scenario)
		{
			std::string line;
			scenario >> line;
			assert(line == "TRUE" || line == "FALSE");
			one_collides_into_two = (line == "TRUE");
			scenario >> line;
			assert(line == "TRUE" || line == "FALSE");
			two_collides_into_one = (line == "TRUE");

			ReadEntity(scenario, entity1);
			ReadEntity(scenario, entity2);
		}

		void ConstructCollisionShape(const CollisionTestEntity& entity, std::unique_ptr<entity::AbstractCollisionShape>&
			shape)
		{
			if (entity.collision_vertices.size() != 2)
			{
				shape = std::make_unique<entity::TriangulatedPolyNaiveRotation>(entity.orientation, entity.position, entity.collision_vertices, entity.triangles);
			}
			else
			{
				//TODO: Handle off-center circles.
				geo::real radius = (entity.collision_vertices[1] - entity.collision_vertices[0]).length();
				shape = std::make_unique<entity::Circle>(entity.orientation, entity.position, radius);
			}
		}

	public:

		TEST_METHOD(AllScenarios)
		{
			std::filesystem::path scenario_file_folder = std::filesystem::relative(R"(..\..\Test\CollisionTestScenarios)");
			for (const auto& file : std::filesystem::directory_iterator(scenario_file_folder))
			{
				std::wstring fail_message1 = file.path().wstring() + L": 1 -> 2 collision is not detected.";
				std::wstring fail_message2 = file.path().wstring() + L": 2 -> 1 collision is not detected.";

				std::ifstream scenario(file.path().string());
				ReadScenario(scenario);

				std::unique_ptr<entity::AbstractCollisionShape> shape1;
				std::unique_ptr<entity::AbstractCollisionShape> shape2;

				ConstructCollisionShape(entity1, shape1);
				ConstructCollisionShape(entity2, shape2);

				geo::EmptyFrame dummy_frame{ -10e20, 10e20, -10e20, 10e20 };

				Assert::AreEqual(one_collides_into_two, shape2->InviteForCollision(dummy_frame, dummy_frame, *shape1), fail_message1.c_str());
				Assert::AreEqual(two_collides_into_one, shape1->InviteForCollision(dummy_frame, dummy_frame, *shape2), fail_message2.c_str());
			}
		}

	};

}
