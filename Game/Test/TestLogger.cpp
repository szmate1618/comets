#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\Utilities\Logger.hpp"

#include <string>
#include <regex>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Test
{

	TEST_CLASS(Socket)
	{

		std::stringstream buffer; //We redirect cout into this buffer.
		std::streambuf * old; //The original state is saved into and restored from this buffer.

		TEST_METHOD_INITIALIZE(InitializerLoggerTests)
		{
			old = std::cout.rdbuf(buffer.rdbuf());
		}

		TEST_METHOD_CLEANUP(CleanupLoggerTests)
		{
			std::cout.rdbuf(old);
		}

		std::regex timestamp_format{ "[0-9]{10}" };

		std::string GetTimeStampFromEntry(std::string entry)
		{
			return entry.substr(0, 10);
		}

		std::string GetSeverityFromEntry(std::string entry)
		{
			return entry.substr(11, 5);
		}

		std::string GetMessageFromEntry(std::string entry)
		{
			return entry.substr(17, buffer.str().size() - 17); //Don't trim expected newline, we want to check if it's really there.
		}

	public:

		TEST_METHOD(ConstructorDestructorLogEntry)
		{
			std::string severity{ "info_" };
			std::string construction_message{ "Logger instance initialized with sync_with_stdio(false).\n" };
			std::string destruction_message{ "Logger instance destructed.\n" };


			{
				util::Logger testLog; //Only instantiated here for testing, normally the predefined global instance should be use from Logger.hpp.
				Assert::IsTrue(std::regex_match(GetTimeStampFromEntry(buffer.str()), timestamp_format), L"Incorrect construction entry timestamp format.");
				Assert::AreEqual(severity, GetSeverityFromEntry(buffer.str()), L"Incorrect construction entry severity level.");
				Assert::AreEqual(construction_message, GetMessageFromEntry(buffer.str()), L"Incorrect construction entry message.");
				buffer.str(""); //Apparently this is how you empty a stringstream.
				buffer.clear(); //And then we clear the potential error state, whatever it means.
			}

			Assert::IsTrue(std::regex_match(GetTimeStampFromEntry(buffer.str()), timestamp_format), L"Incorrect cdestruction entry timestamp format.");
			Assert::AreEqual(severity, GetSeverityFromEntry(buffer.str()), L"Incorrect destruction entry severity level.");
			Assert::AreEqual(destruction_message, GetMessageFromEntry(buffer.str()), L"Incorrect destruction entry message.");
		}

	};

}
