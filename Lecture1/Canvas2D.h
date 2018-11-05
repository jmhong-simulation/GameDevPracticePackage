#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include <vector>
#include <string>

#include "RGB.h"
#include "Vector2.h"
#include "Vector3.h"

namespace jm
{
	using vec2 = Vector2<float>;
	using vec3 = Vector3<float>;

	class Canvas2D
	{
	public:
		int width = 640;
		int height = 480;

		GLFWwindow* glfw_window = nullptr;

	public:
		Canvas2D(const std::string& _title, const int& _width, const int& _height, 
			const bool & use_full_screen = false, const int & display_ix = 0);

		~Canvas2D();

		void reportErrorAndExit(const std::string& function_name, const std::string& message);

		float getRadian(const float& degree) // degree to radian
		{
			return degree / 180.0f * 3.141592f;
		}

		void drawLine(const RGB& color0, const vec2& position0, const vec3& color1, const vec2& position1)
		{
			glBegin(GL_LINES);
			{
				glColor3fv(&color0[0]);
				glVertex2fv(&position0[0]);
				glColor3fv(&color1[0]);
				glVertex2fv(&position1[0]);
			}
			glEnd();
		}

		void beginTransformation()
		{
			glPushMatrix();
		}

		void endTransformation()
		{
			glPopMatrix();
		}

		void translate(const float& pos_x, const float& pos_y)
		{
			glTranslatef(pos_x, pos_y, 0.0);
		}

		void rotate(const float& degree)
		{
			glRotatef(degree, 0.0, 0.0, 1.0);
		}

		void scale(const float& scale_x, const float& scale_y)
		{
			glScalef(scale_x, scale_y, 1.0);
		}

		void drawFilledBox(const RGB& color, const float& width, const float& height)
		{
			const vec2 left_bottom(-0.5f * width, -0.5f * height);

			glColor3fv(&color[0]);
			glBegin(GL_QUADS);
			{
				glVertex2f(left_bottom.x, left_bottom.y);
				glVertex2f(left_bottom.x + width, left_bottom.y);
				glVertex2f(left_bottom.x + width, left_bottom.y + height);
				glVertex2f(left_bottom.x, left_bottom.y + height);
			}
			glEnd();
		}

		void drawFilledCircle(const RGB& color, const float& radius, const int& num_segments = 100)
		{
			const float d_theta = 3.141592f * 2.0f / static_cast<float>(num_segments);

			glColor3fv(&color[0]);

			glBegin(GL_TRIANGLE_FAN);
			{
				glVertex2f(0.0f, 0.0f);

				float theta = 0;
				for (int i = 0; i < num_segments; ++i)
				{
					glVertex2f(radius * cos(theta), radius * sin(theta));

					theta += d_theta;
				}
				glVertex2f(radius, 0.0f);

			}
			glEnd();
		}

		void drawCircle(const RGB& color, const float& radius, const int& num_segments = 100)
		{
			const float d_theta = 3.141592f * 2.0f / (float)num_segments;

			glColor3fv(&color[0]);

			glBegin(GL_LINE_LOOP);
			{
				float theta = 0;
				for (int i = 0; i < num_segments; ++i)
				{
					glVertex2f(radius * cos(theta), radius * sin(theta));

					theta += d_theta;
				}
			}
			glEnd();
		}

		bool isKeyPressed(const int& key)
		{
			return glfwGetKey(glfw_window, key) == GLFW_PRESS;
		}

		bool isKeyReleased(const int & key)
		{
			return glfwGetKey(glfw_window, key) == GLFW_RELEASE;
		}

		template <typename T_DRAW_FUNC>
		void render(const T_DRAW_FUNC & draw_func)
		{
			glfwMakeContextCurrent(glfw_window);

			glClearColor(1, 1, 1, 1);			 // while background
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glMatrixMode(GL_MODELVIEW);

			draw_func();

			glfwSwapBuffers(glfw_window); // double buffering

			glfwPollEvents();
		}

		template <typename T_DRAW_FUNC>
		void show(const T_DRAW_FUNC & draw_func)
		{
			while (!glfwWindowShouldClose(glfw_window))
			{
				render(draw_func);
			}

			glfwTerminate();
		}
	};
}