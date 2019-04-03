#pragma once
#include <iostream>
#include <vector>
#include "SDL_mixer.h"
using namespace std;

class AudioManager
{
private:
	vector<Mix_Music*> m_vMusic;
	vector<Mix_Chunk*> m_vSounds;

public:
	~AudioManager();
	void SetMusicVolume(int v);
	// Note the default parameters of the two play functions below.
	void PlayMusic(int idx = 0, int loops = -1);
	void PlaySound(int idx, int channel = -1, int loops = 0);
	void LoadMusic(const char* s);
	void LoadSound(const char* s);
	void ToggleMusic();
	void ClearMusic();
	void ClearSounds();
};