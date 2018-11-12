#pragma once

#include "Game2D.h"

namespace jm
{
	class SolarSystem : public Game2D
	{
		float time = 0.0f;

	public:
		void update() override
		{
			beginTransformation();
			{
				drawFilledStar(Colors::gold, 0.2f, 0.13f);	// Sun

				translate(0.5f, 0.0f);
				drawFilledCircle(Colors::blue, 0.1f);		// Earth

				translate(0.2f, 0.0f);
				drawFilledCircle(Colors::yellow, 0.05f);	// Moon
			}
			endTransformation();

			time += this->getTimeStep();

		}
	};
}