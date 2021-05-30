#pragma once
#include <string>
#include <chrono>
#include <iostream>
class SimpleTimer
{
	using TimePoint = std::chrono::high_resolution_clock::time_point;
public:
	SimpleTimer() = delete;
	SimpleTimer(const std::string Name)
		:m_Name(Name)
	{		
		m_Start= std::chrono::high_resolution_clock::now();
	}

	~SimpleTimer()
	{
		TimePoint end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - m_Start;
		std::cout << "[" << m_Name << "] time : " << (float)std::chrono::duration_cast<std::chrono::microseconds>(diff).count()/1000 << " ms\n";
	}

private:
	TimePoint m_Start;
	std::string m_Name;
};