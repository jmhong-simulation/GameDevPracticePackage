#pragma once

#include "Game2D.h"

namespace jm
{
	class House
	{
	public:
		vec2 pos;
		float angle;
		RGB roof_color;

		void draw();
	};
}