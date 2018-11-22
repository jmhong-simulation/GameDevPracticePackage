#include "Timer.h"

namespace jm
{
	void Timer::reset()
	{
		start_time = clock_t::now();
	}
	
	void Timer::start()
	{
		reset();
	}
	
	void Timer::stop()
	{
		end_time = clock_t::now();
	}
	
	double Timer::getElapsedMilli() const
	{
		const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

		return static_cast<double>(elapsed);
	}
	
	double Timer::stopAndGetElapsedMilli()
	{
		stop();

		return getElapsedMilli();
	}
}
