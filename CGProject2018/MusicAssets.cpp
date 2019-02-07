#include "MusicAssets.h"
#include "SDL2/SDL.h"
#include "Tools.h"

MusicAssets* MusicAssets::sInstance = NULL;

MusicAssets* MusicAssets::Instance() {
	
	// 8a ginei initialize mono mia fora
	if (sInstance == NULL) {
		sInstance = new MusicAssets();
	}

	return sInstance;
}

void MusicAssets::Release() {
	delete sInstance;
	sInstance = NULL;
}

MusicAssets::MusicAssets() {
	
}

MusicAssets::~MusicAssets() {
	//clear the maps containing the music assets
	for (auto m : mMusic) {
		if (m.second != NULL) {
			Mix_FreeMusic(m.second);
		}
	}
	mMusic.clear();
	
	for (auto m : mSFX) {
		if (m.second != NULL) {
			Mix_FreeChunk(m.second);
		}
	}
	mSFX.clear();
}

Mix_Music* MusicAssets::GetMusic(std::string filename) {
	std::string fullpath = Tools::GetFolderPath("../Data/Music/");
	fullpath.append(filename);
	printf("the full path: %s",fullpath.c_str());
	if (mMusic[fullpath] == nullptr) {

		mMusic[fullpath] = Mix_LoadMUS(fullpath.c_str());
		if (mMusic[fullpath] == nullptr) {
			printf("Error loading music in file: %s and error: %s", filename.c_str(), Mix_GetError());
		}
	}
	
	//return the music
	return mMusic[fullpath];
}


Mix_Chunk* MusicAssets::GetSFX(std::string filename) {
	std::string fullpath = Tools::GetFolderPath("../Data/Music/");
	fullpath.append(filename);

	if (mSFX[fullpath] == nullptr) {

		mSFX[fullpath] = Mix_LoadWAV(fullpath.c_str());
		if (mSFX[fullpath] == nullptr) {
			printf("Error loading special effects sound");
		}
	}

	//return the special effect
	return mSFX[fullpath];
}
