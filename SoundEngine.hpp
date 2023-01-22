#ifndef SOUNDENGINE_HPP

#define SOUNDENGINE_HPP
#include<irrKlang.h>
#include<iostream>
using namespace irrklang;
class SoundEngine {
public:
	SoundEngine();
	void stopSound();
	void playSound(std::string FileName);
private:
	irrklang::ISoundEngine* sound;
};
#endif // !SOUNDENGINE_HPP