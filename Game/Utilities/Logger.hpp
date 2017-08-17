#pragma once

#include <iostream>
#include <ctime>

namespace util
{
	
	enum severity { trace, debug, info, warn, error, fatal };

	class Logger
	{

	public:

		static void Log(severity severity, const char* message)
		{
			std::cout << std::time(nullptr) << " " << severity << " " << message << std::endl;
			std::cout.flush();
		}

	private:

		class Initializer
		{
		public:
			Initializer()
			{ 
				std::ios_base::sync_with_stdio(false);
				Log(info, "Logger initialized with sync_with_stdio(false).");
			}
		};

		static Initializer initialize;

	};

}
