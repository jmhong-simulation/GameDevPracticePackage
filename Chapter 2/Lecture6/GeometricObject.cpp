#include "GeometricObject.h"

#include "Triangle.h"
#include "Circle.h"
#include "Box.h"
#include "Star.h"

namespace jm
{
	GeometricObject * GeometricObject::makeTriangle(const RGB & _color, const vec2 & _pos, const float & _size)
	{
		return new Triangle(_color, _pos, _size);
	}
	
	GeometricObject * GeometricObject::makeCircle(const RGB & _color, const vec2 & _pos, const float & _size)
	{
		return new Circle(_color, _pos, _size);
	}
	
	GeometricObject * GeometricObject::makeBox(const RGB & _color, const vec2 & _pos, const float & _width, const float & _height)
	{
		return new Box(_color, _pos, _width, _height);
	}

	GeometricObject * GeometricObject::makeStar(const RGB & _color, const vec2 & _pos, const float & _os, const float & _is)
	{
		return new Star(_color, _pos, _os, _is);
	}
}