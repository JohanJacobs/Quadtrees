#include "Utils\Log\Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace UTILS
{	
	Ref<spdlog::logger> Log::s_Logger;
	bool Log::s_LoggerInit = false;
	
	void Log::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(CreateRef<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(CreateRef<spdlog::sinks::basic_file_sink_mt>("Logger.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_Logger = CreateRef<spdlog::logger>("UTILS", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_Logger);

		s_Logger->set_level(spdlog::level::trace);
		s_Logger->flush_on(spdlog::level::trace);

		s_LoggerInit = true;
		ULOG_INFO("logger is up..");
	}	
}