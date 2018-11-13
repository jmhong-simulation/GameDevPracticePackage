#pragma once

#include <iostream>
#include <random>
#include <ctime>
#include "Vector2.h"

namespace jm
{
	class RandomNumberGenerator
	{
		using vec2 = Vector2<float>;

	public:
		std::mt19937 mersenne;

		RandomNumberGenerator()
			: mersenne(static_cast<unsigned int>(std::time(nullptr)))
		{
		}

		~RandomNumberGenerator()
		{
		}

		int getInt(const int& min, const int& max)
		{
			return std::uniform_int_distribution<>(min, max)(mersenne);
		}

		float getFloat(const float& min, const float& max)
		{
			return static_cast<float>(std::uniform_real_distribution<>(min, max)(mersenne));
		}

		double getDouble(const double& min, const double& max)
		{
			return std::uniform_real_distribution<>(min, max)(mersenne);
		}

		vec2 getFloatVector(const float& min, const float& max)
		{
			return vec2(getFloat(min, max), getFloat(min, max));
		}
	};
}
