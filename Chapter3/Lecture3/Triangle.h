#pragma once

#include "GeometricObject.h"

namespace jm
{
	class Triangle : public GeometricObject
	{
	public:
		float size;

		Triangle(const RGB & _color, const vec2 & _pos, const float & _size)
		{
			init(_color, _pos, _size);
		}

		~Triangle()
		{
			printf("Triangle destructor\n");
		}

		void init(const RGB & _color, const vec2 & _pos, const float & _size)
		{
			GeometricObject::init(_color, _pos);
			size = _size;
		}

		void drawGeometry() const override
		{
			drawFilledTriangle(color, size);
		}
	};
}