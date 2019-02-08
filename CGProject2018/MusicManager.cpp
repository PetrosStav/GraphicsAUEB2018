#include "MusicManager.h"
#include <iostream>
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
	isMusicPaused = false;
	mAssetManager = MusicAssets::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		printf("Mixer Initialization Error");
	}

}

MusicManager::~MusicManager() {
	mAssetManager = NULL;
	Mix_Quit();
}

void MusicManager::PlayMusic(std::string filename,int music_type,int loops) {
	
	//Mix_Music * music = mAssetManager->GetMusic(filename);
	Mix_PlayMusic(mAssetManager->GetMusic(filename), loops);
	if (music_type == 0) {
		// imperial_march
		Mix_VolumeMusic(30);
	}
	else if (music_type == 1) {
		// dark
		Mix_VolumeMusic(128);
	}
	else if (music_type == 2) {
		//bensound_epic / epic boss
		Mix_VolumeMusic(25);
	}
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

void MusicManager::QuitMusic() {
	//Mix_FadeOutMusic(10);
	Mix_HaltMusic();
}

void MusicManager::PlaySFX(std::string filename, int sfx_type ,int loops, int channel) {
	Mix_Chunk* chunk = mAssetManager->GetSFX(filename);
	if (sfx_type == 0) {
		//tower
		Mix_VolumeChunk(chunk, 10);
	}
	else if (sfx_type == 1) {
		//skeleton_breath
		std::cout << "BREATHHHHH" << std::endl;
		Mix_VolumeChunk(chunk, 15);
	}
	else if (sfx_type == 2) {
		//vader breath
		Mix_VolumeChunk(chunk, 15);
	}
	else if (sfx_type == 3) {
		//death sound / game_over / coin_fall
		Mix_VolumeChunk(chunk, 20);

	}
	else if (sfx_type == 4) {
		//saber on / saber off
		Mix_VolumeChunk(chunk, 20);
	}
	
	Mix_PlayChannel(channel, chunk, loops);
}

void MusicManager::setMusicPause(bool pause) {
	isMusicPaused = pause;
}

bool MusicManager::getMusicIsPaused() {
	return isMusicPaused;
}

void MusicManager::QuitSFX(int channel) {
	Mix_HaltChannel(channel);
}
