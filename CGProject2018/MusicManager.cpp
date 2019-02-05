#include "MusicManager.h"

MusicManager* MusicManager::sInstance = NULL;

MusicManager* MusicManager::Instance() {

	if (sInstance == NULL) {
		sInstance = new MusicManager();
	}

	return sInstance;
}

void MusicManager::Release() {
	delete sInstance;
	sInstance = NULL;
}

MusicManager::MusicManager() {

	mAssetManager = MusicAssets::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		printf("Mixer Initialization Error");
	}

}

MusicManager::~MusicManager() {
	mAssetManager = NULL;
	Mix_Quit();
}

void MusicManager::PlayMusic(std::string filename, int loops) {
	Mix_PlayMusic(mAssetManager->GetMusic(filename), loops);
}

void MusicManager::PauseMusic() {
	if (Mix_PlayingMusic() != 0) {
		Mix_PauseMusic();
	}
}

void MusicManager::ResumeMusic() {
	if (Mix_PausedMusic() != 0) {
		Mix_ResumeMusic();
	}
}

void MusicManager::PlaySFX(std::string filename, int loops, int channel) {
	Mix_PlayChannel(channel, mAssetManager->GetSFX(filename), loops);
}