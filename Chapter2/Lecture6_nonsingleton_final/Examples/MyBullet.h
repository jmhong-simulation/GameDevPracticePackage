#pragma once

#include "Game2D.h"
//#include "SoundEngine_Singleton.h"
#include "SoundEngine.h"

namespace jm
{
	class MyBullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);

		SoundEngine * sound_engine = nullptr;

		MyBullet(SoundEngine * _sound_engine)
		{
			sound_engine = _sound_engine;

			sound_engine->playSound("missile");
			//SoundEngine_Singleton::getInstance()->playSound("missile");
		}

		~MyBullet()
		{
			sound_engine->stopSound("missile");
			//SoundEngine_Singleton::getInstance()->stopSound("missile");
		}

		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
			drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
			endTransformation();
		}

		void update(const float& dt)
		{
			center += velocity * dt;
		}
	};

}
