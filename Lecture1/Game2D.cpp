#include "Game2D.h"

namespace jm
{
	Game2D::Game2D(const std::string & _title, const int & _width, const int & _height, const bool & use_full_screen, const int & display_ix)
		: width(_width), height(_height)
	{
		if (!glfwInit()) reportErrorAndExit(__FUNCTION__, "glfw initialization");

		const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		int num_monitors;
		GLFWmonitor ** monitors = glfwGetMonitors(&num_monitors);

		if (!use_full_screen) {
			glfw_window = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL);

			// center window
			int display_w, display_h;
			glfwMakeContextCurrent(glfw_window);
			glfwGetFramebufferSize(glfw_window, &display_w, &display_h);

			if (num_monitors == 3) // find center display
				glfwSetWindowPos(glfw_window, (mode->width - display_w) / 2 - mode->width, (mode->height - display_h) / 2);
			else
				glfwSetWindowPos(glfw_window, (mode->width - display_w) / 2, (mode->height - display_h) / 2);
		}
		else {
			if (display_ix < num_monitors) // display_ix is valid
				glfw_window = glfwCreateWindow(mode->width, mode->height, _title.c_str(), monitors[display_ix], NULL);
			else
				glfw_window = glfwCreateWindow(mode->width, mode->height, _title.c_str(), glfwGetPrimaryMonitor(), NULL);

			// full screen resolution
			width = mode->width;
			height = mode->height;
		}

		if (!glfw_window) reportErrorAndExit(__FUNCTION__, "Window initialization");

		glfwMakeContextCurrent(glfw_window);

		// Initialize GLEW
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) reportErrorAndExit(__FUNCTION__, "glew initialization");

		const float aspect_ratio = (float)width / (float)height;
		glViewport(0, 0, width, height);
		glOrtho(-aspect_ratio, aspect_ratio, -1.0, 1.0, -1.0, 1.0);
		std::cout << "Display width = " << width << " height = " << height <<
			" Aspect ratio is " << aspect_ratio << std::endl;

		// anti-aliasing
		glfwWindowHint(GLFW_SAMPLES, 32);
		glEnable(GL_LINE_SMOOTH);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Game2D::~Game2D()
	{
		glfwDestroyWindow(glfw_window);
		// 'delete glfw_window' doesn't work
	}

	void Game2D::reportErrorAndExit(const std::string & function_name, const std::string & message)
	{
		std::cout << "Error: " << function_name << " " << message << std::endl;

		glfwTerminate();
		getchar(); // pause to read error message
		exit(1);
	}

	bool Game2D::isKeyPressed(const int & key)
	{
		return glfwGetKey(glfw_window, key) == GLFW_PRESS;
	}

	bool Game2D::isKeyReleased(const int & key)
	{
		return glfwGetKey(glfw_window, key) == GLFW_RELEASE;
	}

	void Game2D::run()
	{
		while (!glfwWindowShouldClose(glfw_window))// main loop
		{
			if (isKeyPressed(GLFW_KEY_ESCAPE)) {
				std::cout << "ESC key ends main loop" << std::endl;
				break;
			}

			// pre draw
			glfwMakeContextCurrent(glfw_window);
			glClearColor(1, 1, 1, 1);			 // while background
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);

			draw();	// the major worker function

					// post draw
			glfwSwapBuffers(glfw_window); // double buffering
			glfwPollEvents();
		}

		glfwTerminate();
	}
}