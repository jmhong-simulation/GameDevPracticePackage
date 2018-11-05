#pragma once

#include "Game2D.h"

namespace jm
{
	float getRadian(const float& degree);

	void drawLine(const RGB& color0, const vec2& position0, const vec3& color1, const vec2& position1);

	void beginTransformation();
	void endTransformation();
	
	void translate(const float& pos_x, const float& pos_y);
	void rotate(const float& degree);
	void scale(const float& scale_x, const float& scale_y);

	void drawCircle(const RGB& color, const float& radius, const int& num_segments = 100);
	void drawFilledBox(const RGB& color, const float& width, const float& height);
	void drawFilledCircle(const RGB& color, const float& radius, const int& num_segments = 100);
}
