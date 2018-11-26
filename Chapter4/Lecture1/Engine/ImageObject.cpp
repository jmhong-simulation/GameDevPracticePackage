#include "ImageObject.h"

// https://learnopengl.com/Getting-started/Textures
// vcpkg install stb:x64-windows
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace jm
{
	// Use tr_r, tr_g, tr_b set transparent color

	void ImageObject::init(const string & filename, const int tr_r, const int tr_g, const int tr_b)
	{
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		int width, height, n_ch;
		unsigned char *data = stbi_load(filename.c_str(), &width, &height, &n_ch, 0);

		if (data)
		{
			if (n_ch == 4)
			{
				int count = 0;
				for (int j = 0; j < height; ++j)
					for (int i = 0; i < width; ++i)
					{
						unsigned char & r = data[count];
						unsigned char & g = data[count + 1];
						unsigned char & b = data[count + 2];

						if (r == tr_r && g == tr_g && b == tr_b)
						{
							data[count + 3] = 0; // alpha = 0 -> transparent
						}

						count += 4;
					}
			}

			//cout << width << " " << height << " " << n_ch << endl;

			ratio = static_cast<float>(width) / static_cast<float>(height);

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			if (n_ch == 4)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			else if (n_ch == 3)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else
			{
				printf("Use RGB or RGBA images. Your input image has %d channels.", n_ch);
			}

			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		stbi_image_free(data);
	}
	
	void ImageObject::draw()
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		beginTransformation();

		scale(ratio * 0.5f, 1.0f * 0.5f);

		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glBegin(GL_QUADS);

		glColor3f(1.0f, 1.0f, 1.0f);

		// upside down texture coordinates
		glTexCoord2d(0.0f, 1.0f);
		glVertex2d(-1.0f, -1.0f);

		glTexCoord2d(1.0f, 1.0f);
		glVertex2d(1.0f, -1.0f);

		glTexCoord2d(1.0f, 0.0f);
		glVertex2d(1.0f, 1.0f);

		glTexCoord2d(0.0f, 0.0f);
		glVertex2d(-1.0f, 1.0f);

		/*glTexCoord2d(0.0f, 0.0f);
		glVertex2d(-1.0f, -1.0f);

		glTexCoord2d(1.0f, 0.0f);
		glVertex2d(1.0f, -1.0f);

		glTexCoord2d(1.0f, 1.0f);
		glVertex2d(1.0f, 1.0f);

		glTexCoord2d(0.0f, 1.0f);
		glVertex2d(-1.0f, 1.0f);*/

		glEnd();

		endTransformation();

		glDisable(GL_TEXTURE_2D);
	}
}
