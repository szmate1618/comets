#include "Logger.hpp"


namespace util
{

	//TODO: Maybe make Logger header-only?
	std::mutex Logger::static_cout_lock;

	Logger Log;

	Logger::Logger()
	{
		std::ios_base::sync_with_stdio(false);
		(*this)(info, "Logger instance initialized with sync_with_stdio(false).");
	}

	Logger::~Logger()
	{
		(*this)(info, "Logger instance destructed.");
	}

	void Logger::operator()(const severity_level severity, std::string message) const
	{
		std::lock_guard<std::mutex> lock{ static_cout_lock };

		const char * severity_text;
		switch (severity)
		{
		case trace: { severity_text = "trace"; break; }
		case debug: { severity_text = "debug"; break; }
		case info: { severity_text = "info_"; break; }
		case warn: { severity_text = "warn_"; break; }
		case error: { severity_text = "error"; break; }
		case fatal: { severity_text = "fatal"; break; }
		default:
		{
			severity_text = "?????";
			(*this)(warn, std::string("Unkown severity level: ") + std::to_string(severity) + std::string("."));
			break;
		}
		}
		std::cout << std::time(nullptr) << "\t" << severity_text << "\t" << message << "\n";
		std::cout.flush();
	}

	void Logger::operator()(const severity_level severity, const char* message) const
	{
		(*this)(severity, std::string(message));
	}

}
