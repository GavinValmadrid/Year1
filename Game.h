#pragma once
#include <vector>
#include "AudioManager.h"
#include "FSM.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#define FPS 60
using namespace std;

class Game
{
private:
	bool m_bRunning;
	bool m_bGotTick;
	bool m_bSpaceOk;
	bool m_bLeftMouse = false; // Keeps track of left mouse button state.
	int m_iMouseX, m_iMouseY;  // Variables to hold mouse positions.
	const Uint8* m_iKeystates;
	SDL_Window* m_pWindow;
	SDL_Texture* m_pSprText;
	SDL_Surface* m_pSprSurf;
	SDL_Renderer* m_pRenderer;
	AudioManager* m_pAM;
	StateMachine* m_pFSM; // Pointer to the StateMachine object created dynamically.
	Game() :m_bRunning(false), m_bGotTick(false), m_bSpaceOk(true) {}

public:
	static Game* Instance();
	SDL_Window* GetWindow() { return m_pWindow; }
	SDL_Renderer* GetRenderer() { return m_pRenderer; }
	SDL_Texture* GetSprTexture() { return m_pSprText;  }
	AudioManager* GetAM() { return m_pAM; }
	StateMachine* GetFSM() { return m_pFSM; }
	int GetMouseX() { return m_iMouseX; } 
	int GetMouseY() { return m_iMouseY; }
	int GetLeftMouse() { return m_bLeftMouse; }
	void SetLeftMouse(bool b) { m_bLeftMouse = b; }
	void QuitGame() { m_bRunning = false; }
	bool Init(const char* title, const int xpos, const int ypos, 
		      const int width, const int height, const int flags);
	bool Running();
	bool KeyDown(SDL_Scancode c);
	bool Tick();
	void Update();
	void HandleEvents();
	void Render();
	void Clean();
	bool GetSpaceOk() { return m_bSpaceOk; }
	void SetSpaceOk(bool b) { m_bSpaceOk = b; }
};