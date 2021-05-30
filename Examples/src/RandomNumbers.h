#pragma once
#include <random>
#include <type_traits>
#include <memory>
/*
	simple static class to generate random numbers 
*/
class RandomNumbers
{
public:	
	template<typename T>
	static constexpr T get(T min, T max)
	{
		std::uniform_real_distribution<>dist(min, max);				
		return (T)dist(s_Data->Generator);
	}
private:
	struct RandomNumbersData
	{
		std::random_device RandomDevice;
		std::mt19937 Generator{ RandomDevice()};		
	};
	static std::unique_ptr<RandomNumbersData> s_Data;
};
std::unique_ptr<RandomNumbers::RandomNumbersData> RandomNumbers::s_Data = std::make_unique<RandomNumbers::RandomNumbersData>();
