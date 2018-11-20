#include "SoundEngine_Singleton.h"

namespace jm
{
	SoundEngine_Singleton * SoundEngine_Singleton::instance = nullptr;

	SoundEngine_Singleton * SoundEngine_Singleton::getInstance()
	{
		if (instance == nullptr)
		{
			instance = new SoundEngine_Singleton();
		}

		return instance;
	}
}
