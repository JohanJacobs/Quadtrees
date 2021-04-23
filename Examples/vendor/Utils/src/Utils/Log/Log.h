#pragma once

/*
	Wrapped for the spdlog library. 

	Usage : 
	first run UTILS::Log::Init();

	then to log there are 4 log styles available 
	ULOG_TRACE("message")
	ULOG_INFO("message")
	ULOG_WARN("message")
	ULOG_ERROR("message")

	Thanks to The Cherno (https://www.youtube.com/watch?v=dZr-53LAlOw&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=6) for the idea 
		
*/

#include "Utils\Base.h"
#include "spdlog\spdlog.h"

// ignore warning s from spdlog
#pragma warning(push,0) 
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)

namespace UTILS
{
	class Log
	{
	public:

		static Ref<spdlog::logger>& GetLogger()
		{
			if (!s_LoggerInit)			
				Init();			
			return s_Logger;
		}
	private:
		static void Init();
	private:
		static Ref<spdlog::logger> s_Logger;
		static bool s_LoggerInit;
	};
}

// Logging functions 
#define ULOG_TRACE(...)    ::UTILS::Log::GetLogger()->trace(__VA_ARGS__)
#define ULOG_INFO(...)     ::UTILS::Log::GetLogger()->info(__VA_ARGS__)
#define ULOG_WARN(...)     ::UTILS::Log::GetLogger()->warn(__VA_ARGS__)
#define ULOG_ERROR(...)    ::UTILS::Log::GetLogger()->error(__VA_ARGS__)
