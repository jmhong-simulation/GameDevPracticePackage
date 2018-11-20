#pragma once

#include "Game2D.h"
#include "MyBullet.h"
#include "MyTank.h"
#include "SoundEngine.h"

namespace jm
{
	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		MyBullet *bullet = nullptr;
		//TODO: allow multiple bullets
		//TODO: delete bullets when they go out of the screen

		SoundEngine sound_engine;

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{
			sound_engine.createSound("drumloop.wav", "background_music", true);
			sound_engine.createSound("truck_idle_off_02.wav", "tank_move", true);
			sound_engine.createSound("cannon1.wav", "cannon", false);

			sound_engine.playSound("background_music");
		}

		~TankExample()
		{
			if(bullet != nullptr) delete bullet;
		}

		void update() override
		{
			// move tank
			if (isKeyPressed(GLFW_KEY_LEFT)) {
				tank.center.x -= 0.5f * getTimeStep();
				sound_engine.playSound("tank_move");
			}
			else
			{
				sound_engine.stopSound("tank_move");
			}

			if (isKeyPressed(GLFW_KEY_RIGHT))	tank.center.x += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_UP))		tank.center.y += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	tank.center.y -= 0.5f * getTimeStep();

			// shoot a cannon ball
			if (isKeyPressedAndReleased(GLFW_KEY_SPACE))
			{
				bullet = new MyBullet;
				bullet->center = tank.center;
				bullet->center.x += 0.2f;
				bullet->center.y += 0.1f;
				bullet->velocity = vec2(2.0f, 0.0f);

				sound_engine.playSound("cannon");
			}

			if (bullet != nullptr) bullet->update(getTimeStep());

			// rendering
			tank.draw();
			if (bullet != nullptr) bullet->draw();
		}
	};
}