#pragma once

#include <iostream>
#include <ctime>
#include <string>


namespace util
{
	
	enum severity_level { trace, debug, info, warn, error, fatal };

	class Logger
	{

	public:

		Logger();
		~Logger();
		void operator()(const severity_level, std::string) const;
		void operator()(const severity_level, const char*) const;

	};

	extern Logger Log;

}
