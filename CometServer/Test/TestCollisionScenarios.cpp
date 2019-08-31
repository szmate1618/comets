#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Geometry\Geometry.hpp"
#include "..\Entities\TriangulatedPolyNaiveRotation.hpp"
#include "..\Entities\Circle.hpp"

#include <filesystem>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(TestCollisionScenarios)
	{
	public:

		TEST_METHOD(AllScenarios)
		{
			std::filesystem::path scenario_file_folder = std::filesystem::relative(R"(..\..\Test\CollisionTestScenarios)");
			for (const auto& file : std::filesystem::directory_iterator(scenario_file_folder))
			{
			}
		}

	};

}
