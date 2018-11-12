#pragma once

#include <chrono> // for std::chrono functions

namespace jm
{
	class Timer
	{
	private:
		// Type aliases to make accessing nested type easier
		using clock_t = std::chrono::high_resolution_clock;
		//using second_t = std::chrono::duration<double, std::ratio<1> >;

		std::chrono::time_point<clock_t> start_time, end_time;

	public:
		Timer()
			: start_time(clock_t::now())
		{}

		void reset();
		void start();
		void stop();
		double getElapsedMilli() const;
		double stopAndGetElapsedMilli();
	};
}
