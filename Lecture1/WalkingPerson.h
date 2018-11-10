#pragma once

#include "Game2D.h"

namespace jm
{
	/*
	TODO:
	- add left arm and left leg
	- make a Person class and use it to draw many people.
	- make an Ironman and allow for him to shoot repulsor beam with his right hand
	*/

	class WalkingPerson : public Game2D
	{
		float time = 0.0f;

	public:
		void update() override
		{
			// red face
			beginTransformation();
			translate(0.0f, 0.12f);
			drawFilledCircle(Colors::red, 0.08f);
			translate(0.05f, 0.03f);
			drawFilledCircle(Colors::white, 0.01f);

			endTransformation();

			// blue body
			beginTransformation();
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::blue, 0.13f, 0.2f);
			endTransformation();

			// yellow arm
			beginTransformation();
			rotate(sin(time*5.0f) * 30.0f);					// animation!
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::yellow, 0.05f, 0.18f);
			endTransformation();

			// green leg
			beginTransformation();
			translate(0.0f, -0.6f);
			translate(0.0f, 0.2f);
			rotate(sinf(time*5.0f + 3.141592f) * 30.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::green, 0.1f, 0.4f);
			endTransformation();

			time += this->getTimeStep();
		}
	};
}