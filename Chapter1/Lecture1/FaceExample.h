#pragma once

#include "Game2D.h"

namespace jm
{
	class FaceExample : public Game2D
	{
	public:
		void update() override
		{
			// Big yellow face
			drawFilledCircle(Colors::yellow, 0.8f); // draw background object first

			// Red mouth
			beginTransformation();
			{
				translate(0.0f, -0.6f);
				scale(3.0f, 1.0f);
				drawFilledCircle(Colors::red, 0.1f);
			}
			endTransformation();

			// Blue nose
			beginTransformation();
			{
				rotate(-10.0f);		// 10 degrees rotated 
				scale(1.0f, 2.0f);
				translate(0.0f, -0.1f);
				drawFilledCircle(Colors::blue, 0.1f);
			}
			endTransformation();

			// left eye
			beginTransformation();
			{
				translate(-0.3f, 0.2f);
				rotate(-45.0f);		// 10 degrees rotated 
				drawFilledBox(Colors::black, 0.1f, 0.4f);
				drawFilledBox(Colors::black, 0.4f, 0.1f);
			}
			endTransformation();

			// right eye
			beginTransformation();
			{
				translate(+0.25f, 0.3f);
				rotate(-45.0f);		// 10 degrees rotated 
				drawFilledBox(Colors::olive, 0.1f, 0.4f);
				drawFilledBox(Colors::olive, 0.4f, 0.1f);
			}
			endTransformation();

			for (float x = -0.5f; x < 0.4f; x += 0.05f)
			{
				drawLine(Colors::black, vec2(x, 0.6f), Colors::gray, vec2(x + 0.05f, 0.85f));
			}
		}
	};
}