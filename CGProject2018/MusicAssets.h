#pragma once
#include "SDL2/SDL_mixer.h"
#include <map>

class MusicAssets {
private:

	static MusicAssets* sInstance;
	std::map<std::string, Mix_Music*> mMusic;
	std::map<std::string, Mix_Chunk*> mSFX;


public:

	static MusicAssets* Instance();
	static void Release();
	
	Mix_Music* GetMusic(std::string filename);
	Mix_Chunk* GetSFX(std::string filename);

private:

	MusicAssets();
	~MusicAssets();

};