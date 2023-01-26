#include"SoundEngine.hpp"
SoundEngine::SoundEngine() {
	sound = createIrrKlangDevice();
}
void SoundEngine::playSound(std::string FileName) {
	sound->play2D(FileName.c_str(), true);
}
void SoundEngine::stopSound() {
	sound->stopAllSounds();
}