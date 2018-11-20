#pragma once

#include "fmod.hpp"
#include <iostream>
#include <map>
#include <string>

namespace jm
{
	class SoundEngine
	{
	public:
		FMOD::System  *system = nullptr;
		FMOD::Channel *channel = nullptr;
		std::map<std::string, FMOD::Sound*> sound_map;
		
		FMOD_RESULT   result;
		unsigned int  version;
		void          *extradriverdata = nullptr;

		SoundEngine()
		{
			using namespace std;

			result = FMOD::System_Create(&system);
			if (result != FMOD_OK) {
				cout << "FMOD::System_Create() fail" << endl;
				exit(-1);
			}

			result = system->getVersion(&version);
			if (result != FMOD_OK) {
				cout << "getVersion() fail" << endl;
				exit(-1);
			}
			else printf("FMOD version %08x\n", version);

			result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
			if (result != FMOD_OK) {
				cout << "system->init() fail" << endl;
				exit(-1);
			}

			
		}

		~SoundEngine()
		{
		}

		void createSound(const std::string & filename, const std::string & sound_name, const bool & use_loop)
		{
			sound_map[sound_name] = nullptr;

			auto & sound_ptr = sound_map[sound_name];

			const int loop_flag = use_loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

			result = system->createSound(filename.c_str(), loop_flag, 0, &sound_ptr);
			
			if (result != FMOD_OK) {
				std::cout << "system->createSound() fail" << std::endl;
				exit(-1);
			}
		}

		void playSound(const std::string & sound_name)
		{
			if (sound_map.count(sound_name) <= 0) {
				std::cout << sound_name << " isn't initialized." << std::endl;
				exit(-1);
			}

			const auto & sound_ptr = sound_map[sound_name];

			result = system->playSound(sound_ptr, 0, false, &channel);

			if (result != FMOD_OK) {
				std::cout << "system->playSound() fail" << std::endl;
				exit(-1);
			}
		}
	};
}
