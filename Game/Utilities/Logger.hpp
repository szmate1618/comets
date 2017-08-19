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

		Logger()
		{
			std::ios_base::Init initialize_stream;
			std::ios_base::sync_with_stdio(false);
			(*this)(info, "Logger initialized with sync_with_stdio(false).");
		}

		~Logger()
		{
			(*this)(info, "Logger destructed.");
		}

		void operator()(const severity_level severity, std::string message) const
		{
			const char * severity_text;
			switch (severity)
			{
			case trace: {severity_text = "trace"; break; }
			case debug: {severity_text = "debug"; break; }
			case info: {severity_text = "info_"; break; }
			case warn: {severity_text = "warn_"; break; }
			case error: {severity_text = "error"; break; }
			case fatal: {severity_text = "fatal"; break; }
			default:
			{
				severity_text = "?????";
				(*this)(warn, std::string("Unkown severity level: ") + std::to_string(severity) + std::string("."));
				break;
			}
			}
			std::cout << std::time(nullptr) << "\t" << severity_text << "\t" << message << std::endl;
			std::cout.flush();
		}

	};

	Logger Log;

}
