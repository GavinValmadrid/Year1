#pragma once
#include <vector>
#include "SDL.h"
#define GRAV 12.0
using namespace std;

enum state{running, jumping, rolling, dying};

class Sprite
{
protected:
	SDL_Rect m_rSrc; // Rectangle for source pixels.
	SDL_Rect m_rDst; // Rectangle for destination window.

public:
	Sprite(SDL_Rect s, SDL_Rect d) :m_rSrc(s), m_rDst(d) {}
	SDL_Rect* GetSrcP() { return &m_rSrc; }
	SDL_Rect* GetDstP() { return &m_rDst; }
};

class AnimatedSprite : public Sprite
{
protected:
	state m_state;
	int m_iSprite = 0,	// Which sprite to display for animation.
		m_iSpriteMin,
		m_iSpriteMax,	// How many sprites total.		
		m_iFrame = 0,	// Frame counter.
		m_iFrameMax,	// Number of frames per sprite.
		m_iDeathCtr = 0,
		m_iDeathCtrMax;

public:
	AnimatedSprite(SDL_Rect, SDL_Rect); // Constructor.
	virtual void Update() = 0;
	void Animate();
	void SetJumping();
	void SetRunning();
	void SetRolling();
	void SetDying();
};

class Player : public AnimatedSprite
{
private:
	bool m_bGrounded;
	double m_dAccelX;
	double m_dMaxAccelX;
	double m_dAccelY;
	double m_dVelX;
	double m_dMaxVelX;
	double m_dVelY;
	double m_dMaxVelY;
	double m_dDrag;
	double m_dGrav;
	int m_iDir; // Direction. -1 or 1.
public:
	Player(SDL_Rect, SDL_Rect);
	void SetDir(int dir);
	void SetAccelX(double a) { m_dAccelX = a; }
	void SetAccelY(double a) { m_dAccelY = a; }
	void SetGravity(double a) { m_dGrav = a; }
	bool IsGrounded() { return m_bGrounded && (m_dVelY == 0); }
	void SetGrounded(bool g) { m_bGrounded = g; }
	double GetVelX() { return m_dVelX; }
	double GetVelY() { return m_dVelY; }
	void SetVelX(double v) { m_dVelX = v; }
	void SetVelY(double v) { m_dVelY = v; }
	void SetX(int y) { m_rDst.x = y; }
	void SetY(int y) { m_rDst.y = y; }
	void Stop()
	{
		m_dVelY = 0.0;
		m_dVelX = 0.0;
	}
	void MoveX();
	void Update();
	friend class GameState; // Allows the GameState to access the private of inherited class
};

class Background : public Sprite
{
private:
	int m_iSpeed; // Scroll speed of background.
public:
	Background(SDL_Rect s, SDL_Rect d, int spd):Sprite(s, d), m_iSpeed(spd) {}
	void Update() { m_rDst.x -= m_iSpeed; }
};

// Changing Platform to Obstacle
class Obstacle
{
private:
	Sprite* m_pSprite; // Only used for initialized obstacles.
	bool m_bIsPlatform; // Is it a platform or an instadeath hazard.
	bool m_bRotates; // Does the hazard rotate.
	int m_iX; // X coordinate.
	// Angle - could make it public...
public:
	Obstacle(int, bool = false, SDL_Rect = {0,0,0,0},
		SDL_Rect = {0,0,0,0}, bool = false, bool = false);
	~Obstacle();
	int GetX() { return m_iX; }
	bool IsPlatform() { return m_bIsPlatform; } // Make sure to set ground object to true.
	Sprite* GetSprite() { return m_pSprite; }
	//void Update();
	bool Rotates() { return m_bRotates; }
};
