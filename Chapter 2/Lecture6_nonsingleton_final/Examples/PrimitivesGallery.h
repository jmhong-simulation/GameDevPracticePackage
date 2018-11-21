#pragma once

#include "Game2D.h"

namespace jm
{
	class PrimitivesGallery : public Game2D
	{
	private:
		float time = 0.0f;

	public:
		void update() override
		{
			setLineWidth(3);

			beginTransformation();
			{
				translate(-1.0f, 0.5f); // left top
				drawWiredTriangle(Colors::red, 0.25f);

				translate(0.5f, 0.0f);
				drawFilledTriangle(Colors::blue, 0.25f);

				translate(0.5f, 0.0f);
				drawWiredSquare(Colors::blue, 0.3f);

				translate(0.5f, 0.0f);
				drawFilledSquare(Colors::red, 0.25f);

				translate(0.5f, 0.0f);
				drawFilledBox(Colors::green, 0.2f, 0.3f);

				translate(-2.0f, -0.5f); // next row
				drawLine(Colors::olive, vec2(-0.1f, -0.1f), Colors::blue, vec2(0.1f, 0.1f));
				drawLine(Colors::blue, vec2(0.1f, -0.1f), Colors::olive, vec2(-0.1f, 0.1f));

				translate(0.5f, 0.0f);
				drawWiredPentagon(Colors::red, 0.18f);

				translate(0.5f, 0.0f);
				drawFilledPentagon(Colors::red, 0.18f);

				translate(0.5f, 0.0f);
				beginTransformation();
				rotate(getRadian(time * 360.0f * 10.0f));
				drawFilledStar(Colors::gold, 0.2f, 0.12f);
				endTransformation();

				translate(0.5f, 0.0f);
				drawWiredCircle(Colors::red, 0.15f);

				translate(-2.0f, -0.5f); // next row
				drawWiredRegularConvexPolygon(Colors::gold, 0.18f, 0.0, 3);

				translate(0.5f, 0.0f);
				drawWiredRegularConvexPolygon(Colors::gold, 0.18f, 0.0, 5);

				translate(0.5f, 0.0f);
				drawWiredRegularConvexPolygon(Colors::gold, 0.18f, 0.0, 7);

				translate(0.5f, 0.0f);
				drawWiredRegularConvexPolygon(Colors::gold, 0.18f, 0.0, 9);

				translate(0.5f, 0.0f);
				drawFilledTriangle(Colors::olive, { -0.15f, -0.15f }, { 0.15f, -0.15f }, { 0.1f, 0.15f });
				drawWiredTriangle(Colors::black, { -0.15f, -0.15f }, { 0.15f, -0.15f }, { 0.1f, 0.15f });
			}
			endTransformation();

			time += getTimeStep();
		}
	};
}
