#pragma once

#include "Game2D.h"
#include <string>

namespace jm
{
	using namespace std;

	class ImageObject
	{
	public:
		unsigned int texture;

		float ratio = 1.0f;

		ImageObject()
		{}

		ImageObject(const string & filename)
		{
			init(filename);
		}

		// Use tr_r, tr_g, tr_b set transparent color
		void init(const string & filename, const int tr_r = -1, const int tr_g = -1, const int tr_b = -1);

		void draw();
	};

}
