#include "Timer.h"
namespace UTILS
{

	Timer::Timer(const std::string& name)
		:m_Name(name)
	{
		m_StartTime = std::chrono::steady_clock::now();
		ULOG_INFO("Timer start [" + name + "]");
	}

	Timer::~Timer()
	{
		auto end_time = std::chrono::steady_clock::now();

		auto high_resolution_start_time = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTime);
		auto high_resolution_end_time   = std::chrono::time_point_cast<std::chrono::microseconds>(end_time);
		
		std::chrono::microseconds elapsed_time = high_resolution_end_time.time_since_epoch() - high_resolution_start_time.time_since_epoch();
				
		ULOG_INFO("Timer end [" + m_Name + "] "+ std::to_string(elapsed_time.count()) + " us ( "+ std::to_string(elapsed_time.count()/1000) +" ms )");
	}
}