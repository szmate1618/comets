#include "stdafx.h"
#include "CppUnitTest.h"

#define private public
#include "..\Entities\Universe.hpp"
#undef private

#include <string>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(TestUniverse)
	{

		const std::string tempdir{ "temp\\" };

	public:

		TEST_METHOD(ConstructFromFile)
		{
			//tempdir.
		}
	};

}
