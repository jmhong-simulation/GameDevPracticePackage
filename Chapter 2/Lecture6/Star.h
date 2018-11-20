#pragma once

#include "GeometricObject.h"

namespace jm
{
	class Star : public GeometricObject
	{
	public:
		float outer_radius, inner_radius;

		Star(const RGB & _color, const vec2 & _pos, const float & _outer,
			const float &_inner)
		{
			init(_color, _pos, _outer, _inner);
		}

		void init(const RGB & _color, const vec2 & _pos, const float & _outer,
			const float &_inner)
		{
			GeometricObject::init(_color, _pos);

			outer_radius = _outer;
			inner_radius = _inner;
		}

		void drawGeometry() const override
		{
			//drawFilledBox(Colors::blue, this->width, this->height);
			drawFilledStar(GeometricObject::color, outer_radius, inner_radius);
		}
	};
}
