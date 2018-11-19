#pragma once

#include "Game2D.h"
#include <map>

namespace jm
{
	class Actor
	{
	public:
		virtual void moveUp(float dt) = 0;
	};

	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(Actor& actor, float dt) = 0;
	};

	class UpCommand : public Command 
	{
	public:
		virtual void execute(Actor& actor, float dt) override
		{
			actor.moveUp(dt);
		}
	};

	class MyTank : public Actor
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		//vec2 direction = vec2(1.0f, 0.0f, 0.0f);

		void moveUp(float dt) override
		{
			center.y += 0.5f * dt;
		}

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::green, 0.25f, 0.1f); // body
				translate(-0.02f, 0.1f);
				drawFilledBox(Colors::blue, 0.15f, 0.09f); // turret
				translate(0.15f, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
			}
			endTransformation();
		}
	};

	class InputHandler
	{
	public:
		Command * button_up = nullptr;

		//std::map<int, Command *> key_command_map;

		InputHandler()
		{
			button_up = new UpCommand;
		}

		void handleInput(Game2D & game, Actor & actor, float dt)
		{
			if (game.isKeyPressed(GLFW_KEY_UP))  button_up->execute(actor, dt);

			/*for (auto & m : key_command_map)
			{
				if (game.isKeyPressed(m.first)) m.second->execute(actor, dt);
			}*/
		}
	};

	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		InputHandler input_handler;

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{
			//key mapping
			//input_handler.key_command_map[GLFW_KEY_UP] = new UpCommand;
		}

		~TankExample()
		{
		}

		void update() override
		{
			// move tank
			/*if (isKeyPressed(GLFW_KEY_LEFT))	tank.center.x -= 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_RIGHT))	tank.center.x += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_UP))		tank.center.y += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	tank.center.y -= 0.5f * getTimeStep();*/

			input_handler.handleInput(*this, tank, getTimeStep());

			// rendering
			tank.draw();
		}
	};
}