#include "House.h"

namespace jm
{
	void House::draw()
	{
		// draw a house
		beginTransformation();
		{
			translate(pos);
			rotate(angle);

			// wall
			drawFilledBox(Colors::yellow, 0.2f, 0.2f);

			// roof
			drawFilledTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });
			drawWiredTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });

			// window
			drawFilledBox(Colors::skyblue, 0.1f, 0.1f);
			drawWiredBox(Colors::gray, 0.1f, 0.1f);
			drawLine(Colors::gray, { 0.0f, -0.05f }, Colors::gray, { 0.0f, 0.05f });
			drawLine(Colors::gray, { -0.05f, 0.0f }, Colors::gray, { 0.05f, 0.0f });
		}
		endTransformation();
	}

}