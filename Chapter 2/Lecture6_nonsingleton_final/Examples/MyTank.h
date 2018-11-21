#pragma once

#include "Game2D.h"

namespace jm
{
	class MyTank
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		//vec2 direction = vec2(1.0f, 0.0f, 0.0f);

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::green, 0.25f, 0.1f); // body
				translate(-0.02f, 0.1f);
				drawFilledBox(Colors::blue, 0.15f, 0.09f); // turret
				translate(0.15f, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
			}
			endTransformation();
		}

		void moveLeft(const float& dt)
		{
			center.x -= 0.5f * dt;
		}

		void moveRight(const float& dt)
		{
			center.x += 0.5f * dt;
		}

		void moveUp(const float& dt)
		{
			center.y += 0.5f * dt;
		}

		void moveDown(const float& dt)
		{
			center.y -= 0.5f * dt;
		}
	};

}
