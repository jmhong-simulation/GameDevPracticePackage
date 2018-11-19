#include "Game2D.h"
#include "DrawFunctions.h"

#include <iostream>
#include <iomanip>

namespace jm
{
	Game2D::Game2D(const std::string & _title, const int & _width, const int & _height,
				   const bool & use_full_screen, 
				   const int & display_ix) // for multiple displays
	{
		init(_title, _width, _height, use_full_screen, display_ix);
	}

	Game2D::~Game2D()
	{
		glfwDestroyWindow(glfw_window); // cannot 'delete' glfw_window
	}

	Game2D& Game2D::init(const std::string & _title, const int & _width, const int & _height, const bool & use_full_screen, const int & display_ix)
	{
		if (glfw_window != nullptr){
			std::cout << "Skip second initialization" << std::endl;
			return *this;
		}

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

			width = display_w;
			height = display_h;

			//if (num_monitors == 3) // find center display
			//	glfwSetWindowPos(glfw_window, (mode->width - display_w) / 2 - mode->width, (mode->height - display_h) / 2);
			//else
			//	glfwSetWindowPos(glfw_window, (mode->width - display_w) / 2, (mode->height - display_h) / 2);

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

		return *this; // chaining (See TBC++ 8.7)
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
		if (key_status.count(key) <= 0) key_status[key] = false;

		if (glfwGetKey(glfw_window, key) == GLFW_PRESS)
			key_status[key] = true;
		else
			key_status[key] = false;

		return key_status[key];
	}

	bool Game2D::isKeyReleased(const int & key)
	{
		if (key_status.count(key) <= 0) key_status[key] = false;

		if (glfwGetKey(glfw_window, key) == GLFW_RELEASE)
			key_status[key] = false;
		else
			key_status[key] = true;

		return key_status[key];
	}

	bool Game2D::isKeyPressedAndReleased(const int & key)
	{
		if (key_status.count(key) <= 0) key_status[key] = false; // register key to map

		if (glfwGetKey(glfw_window, key) == GLFW_RELEASE)
		{
			if (key_status[key] == true) {
				key_status[key] = false;
				return true;
			}
			else {
				key_status[key] = false;
				return false;
			}
		}
		else {
			key_status[key] = true;
			return false;
		}
	}

	bool Game2D::isMouseButtonPressed(const int & key)
	{
		if (mbtn_status.count(key) <= 0) mbtn_status[key] = false;

		if (glfwGetMouseButton(glfw_window, key) == GLFW_PRESS)
			mbtn_status[key] = true;
		else
			mbtn_status[key] = false;

		return mbtn_status[key];
	}

	bool Game2D::isMouseButtonReleased(const int & key)
	{
		if (mbtn_status.count(key) <= 0) mbtn_status[key] = false;

		if (glfwGetMouseButton(glfw_window, key) == GLFW_RELEASE)
			mbtn_status[key] = false;
		else
			mbtn_status[key] = true;

		return mbtn_status[key];
	}

	bool Game2D::isMouseButtonPressedAndReleased(const int & mbtn)
	{
		if (mbtn_status.count(mbtn) <= 0) mbtn_status[mbtn] = false; // register key to map

		if (glfwGetMouseButton(glfw_window, mbtn) == GLFW_RELEASE)
		{
			if (mbtn_status[mbtn] == true) {
				mbtn_status[mbtn] = false;
				return true;
			}
			else {
				mbtn_status[mbtn] = false;
				return false;
			}
		}
		else {
			mbtn_status[mbtn] = true;
			return false;
		}
	}

	vec2 Game2D::getCursorPos(const bool& screen_coordinates)
	{
		double x_pos, y_pos;
		glfwGetCursorPos(glfw_window, &x_pos, &y_pos);
		// Note that (0, 0) is left up corner. 
		// This is different from our screen coordinates.
		// 0 <= x <= width - 1
		// height - 1 >= y >= 0 

		if (screen_coordinates) // assumes width >= height
		{
			// upside down y direction
			y_pos = height - y_pos - 1; // 0 <= y <= height - 1

			// rescale and translate zero to center
			y_pos = y_pos / (height - 1); //  0.0 <= y <= 1.0
			y_pos = y_pos * 2.0;		  //  0.0 <= y <= 2.0
			y_pos = y_pos - 1.0;		  // -1.0 <= y <= 1.0

			x_pos = (x_pos / (width - 1) * 2.0 - 1.0) * width / height;

			return vec2(static_cast<float>(x_pos), static_cast<float>(y_pos));
		}
		else
		{
			return vec2(static_cast<float>(x_pos), static_cast<float>(y_pos));
		}
	}

	void Game2D::run()
	{
		if (glfw_window == nullptr)
			init("This is my digital canvas!", 1280, 960, false); // initialize with default setting

		while (!glfwWindowShouldClose(glfw_window))// main loop
		{
			if (isKeyPressed(GLFW_KEY_ESCAPE)) {
				std::cout << "ESC key ends main loop" << std::endl;
				break;
			}

			timer.start();

			// pre draw
			glfwMakeContextCurrent(glfw_window);
			glClearColor(1, 1, 1, 1);			 // while background
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);

			glPushMatrix();

			drawGrid();

			update();	// the major worker function

			glPopMatrix();

			// post draw
			glfwSwapBuffers(glfw_window); // double buffering
			//glfwSetInputMode(glfw_window, GLFW_STICKY_KEYS, GLFW_FALSE); // not working 
			glfwPollEvents();

			//const double dt = timer.stopAndGetElapsedMilli();

			//Debugging
			//std::cout << dt << std::endl;

			//if (dt < spf) // to prevent too high fps
			//{
			//	const auto time_to_sleep = static_cast<int>((spf - dt) * 1000.0f);
			//	std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep));
			//	
			//	//Debugging
			//	//std::cout << "sleep " << time_to_sleep << std::endl;
			//}
		}

		glfwTerminate();
	}
	
	float Game2D::getTimeStep()
	{
		return spf;
	}
	
	void Game2D::drawGrid()
	{
		if (isKeyPressedAndReleased(GLFW_KEY_G)) draw_grid = !draw_grid;

		if (draw_grid) {
			setLineWidth(1);
			jm::drawGrid(Colors::gray, 0.5f); //Note: Game2D::drawGrid() vs jm::drawGrid(...)
		}
	}
}