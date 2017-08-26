#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include <mutex>


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

	private:

		mutable std::mutex static_cout_lock;

	};

	extern Logger Log;

}
