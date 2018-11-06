#pragma once

#include "Game2D.h"

namespace jm
{
	class MyTank
	{
	public:
		vec3 center = vec3(0.0f, 0.0f, 0.0f);
		vec3 direction = vec3(1.0f, 0.0f, 0.0f);

		void draw()
		{
			beginTransformation();
			translate(center.x, center.y);
			drawFilledBox(RGBColors::green, 0.25f, 0.1f);
			translate(-0.02f, 0.1f);
			drawFilledBox(RGBColors::blue, 0.15f, 0.09f);
			translate(0.15f, 0.0f);
			drawFilledBox(RGBColors::red, 0.15f, 0.03f);
			endTransformation();
		}
	};

	class MyBullet
	{
	public:
		vec3 center = vec3(0.0f, 0.0f, 0.0f);
		vec3 velocity = vec3(0.0f, 0.0f, 0.0f);

		void draw()
		{
			beginTransformation();
			translate(center.x, center.y);
			drawFilledRegularConvexPolygon(RGBColors::yellow, 0.02f, 8);
			drawWiredRegularConvexPolygon(RGBColors::gray, 0.02f, 8);
			endTransformation();
		}

		void update(const float& dt)
		{
			center += velocity * dt;
		}

	};

	class TankExample : public Game2D
	{
	public:
		float time = 0.0;

		MyTank tank;

		MyBullet *bullet = nullptr;
		//TODO: allow multiple bullets
		//TODO: delete bullets when they go out of the screen

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{}

		void update() override
		{
			// move tank
			if (isKeyPressed(GLFW_KEY_LEFT))	tank.center.x -= 0.01f;
			if (isKeyPressed(GLFW_KEY_RIGHT))	tank.center.x += 0.01f;
			if (isKeyPressed(GLFW_KEY_UP))		tank.center.y += 0.01f;
			if (isKeyPressed(GLFW_KEY_DOWN))	tank.center.y -= 0.01f;

			// shoot a cannon ball
			if (isKeyPressedAndReleased(GLFW_KEY_SPACE))
			{
				if (bullet != nullptr) delete bullet;
				bullet = new MyBullet;
				bullet->center = tank.center;
				bullet->center.x += 0.2f;
				bullet->center.y += 0.1f;
				bullet->velocity = vec3(2.0f, 0.0f, 0.0f);
			}

			if (bullet != nullptr) bullet->update(1 / 60.0f);

			// rendering
			tank.draw();
			if (bullet != nullptr) bullet->draw();

			time += 1 / 60.0f;

			// sleep 
		}
	};
}