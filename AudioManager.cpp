#include "AudioManager.h"

void AudioManager::SetMusicVolume(int v)
{
	v = (v < 0 ? 0 : (v > MIX_MAX_VOLUME ? MIX_MAX_VOLUME : v)); // Clamps vol from 0 to 128. 
	Mix_VolumeMusic(v);
}

void AudioManager::PlayMusic(int idx, int loops)
{
	Mix_PlayMusic(m_vMusic[idx], loops);
}

void AudioManager::PlaySound(int idx, int channel, int loops)
{
	Mix_PlayChannel(channel, m_vSounds[idx], loops);
}

void AudioManager::LoadMusic(const char* s)
{ // Just a bit of error checking for good measure.
	Mix_Music* t = Mix_LoadMUS(s);
	if (t != nullptr)
		m_vMusic.push_back(t);
	else cout << "Music load fail" << endl;
}

void AudioManager::LoadSound(const char* s)
{
	Mix_Chunk* t = Mix_LoadWAV(s);
	if (t != nullptr)
		m_vSounds.push_back(t);
	else cout << "Sound load fail" << endl;
}

void AudioManager::ToggleMusic()
{
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}

void AudioManager::ClearMusic()
{
	for (int i = 0; i < (int)m_vMusic.size(); i++)
	{
		Mix_FreeMusic(m_vMusic[i]);
		m_vMusic[i] = nullptr;
	}
	m_vMusic.clear();
	m_vMusic.shrink_to_fit();
}

void AudioManager::ClearSounds()
{
	for (int i = 0; i < (int)m_vSounds.size(); i++)
	{
		Mix_FreeChunk(m_vSounds[i]);
		m_vSounds[i] = nullptr;
	}
	m_vSounds.clear();
	m_vSounds.shrink_to_fit();
}

AudioManager::~AudioManager()
{
	cout << "Destroying AudioManager..." << endl;
	ClearMusic();
	ClearSounds();
}