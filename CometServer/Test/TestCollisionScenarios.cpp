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
			bool one_collides_into_two = (line == "TRUE");
			scenario >> line;
			assert(line == "TRUE" || line == "FALSE");
			bool two_collides_into_one = (line == "TRUE");

			ReadEntity(scenario, entity1);
			ReadEntity(scenario, entity2);
		}

	public:

		TEST_METHOD(AllScenarios)
		{
			std::filesystem::path scenario_file_folder = std::filesystem::relative(R"(..\..\Test\CollisionTestScenarios)");
			for (const auto& file : std::filesystem::directory_iterator(scenario_file_folder))
			{
				std::ifstream scenario(file.path().string());
				ReadScenario(scenario);
			}
		}

	};

}
