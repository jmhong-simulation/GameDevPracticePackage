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
#include "RGBColors.h"

namespace jm
{
	using vec2 = Vector2<float>;
	using vec3 = Vector3<float>;

	class Game2D
	{
	private:
		int width = 640;
		int height = 480;

		GLFWwindow* glfw_window = nullptr;

	public:
		Game2D(const std::string& _title, const int& _width, const int& _height,
			const bool & use_full_screen = false, const int & display_ix = 0);

		~Game2D();

		void reportErrorAndExit(const std::string& function_name, const std::string& message);

		bool isKeyPressed(const int& key);
		bool isKeyReleased(const int & key);

		void run();

		virtual void draw() {}
	};
}