#pragma once
#include "MusicAssets.h"

class MusicManager {

private:

	static MusicManager* sInstance;

	MusicAssets* mAssetManager;

public:

	static MusicManager* Instance();
	static void Release();

	//gia -1 paizei panta..gia 0 mia fora gia 1 paizei 2 fores klp
	void PlayMusic(std::string filename, int loops = -1);
	void PauseMusic();
	void ResumeMusic();

	//thelei leei prosoxi me ta channels giati otan exeis polla sound effect an ta exeis sto idio channel 8a kanoun overwrite to ena to allo
	void PlaySFX(std::string filename, int loops = 0, int channel = 0);

private:
	MusicManager();
	~MusicManager();

};