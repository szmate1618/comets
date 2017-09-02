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

		mutable std::mutex static_cout_lock; //TODO: Investigate why I can't declare this as static. Allegedly it's a bug in MSVC's constexpr constructor implementation.
		//See here: https://stackoverflow.com/questions/30766103/why-declare-constrexpr-constructors-for-classes-with-non-trivial-destructors-e

	};

	extern Logger Log;

}
