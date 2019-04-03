#include <algorithm> // For min/max.
#include <cmath>	 // For cos/sin.
#include "Game.h"
#include "Sprites.h"

using namespace std;

AnimatedSprite::AnimatedSprite(SDL_Rect s, SDL_Rect d): Sprite(s, d) {}

void AnimatedSprite::Animate()
{
	if (m_iFrame == m_iFrameMax)
	{
		m_iFrame = 0;
		m_iSprite++;
		if (m_iSprite == m_iSpriteMax)
		{
			m_iSprite = m_iSpriteMin; // 0 will be replaced with m_iSpriteMin
									 // loops back around the sprite sheet
		}
	}
	m_iFrame++;
	m_rSrc.x = m_rSrc.w * m_iSprite; // Updates the source based on the animation
}

void AnimatedSprite::SetJumping() 
{
	m_state = jumping;
	m_iFrame = 0; // Reseting the frame
	m_iFrameMax = 1; 
	m_iSprite = m_iSpriteMin = 8; // Counter minimum
	m_iSpriteMax = 9; // When it get to 9, loops back to 8
	m_rSrc.y = 256; // This changes to rolling and dying
	// m_rBound.w = 64;
	// m_rBound.h= 124;
}
void AnimatedSprite::SetRunning()
{
	m_state = running;
	m_iFrame = 0; 
	m_iFrameMax = 6; // speed of animation.
	m_iSprite = m_iSpriteMin = 0; // 0 = starts at the index of 0
	m_iSpriteMax = 8; // 0-7 the index of the cycle
	m_rSrc.y = 256; 
	// m_rBound.w = 64;
	// m_rBound.h= 124;
}
void AnimatedSprite::SetRolling()
{
	m_state = rolling;
	m_iFrame = 0; 
	m_iFrameMax = 6;
	m_iSprite = m_iSpriteMin = 0; 
	m_iSpriteMax = 4; 
	m_rSrc.y = 256+128; 
	// m_rBound.w = 64;
	// m_rBound.h = 60;
}

void AnimatedSprite::SetDying()
{
	m_state = dying;
	m_iFrame = 0;
	m_iFrameMax = 12; // Double the time it takes
	m_iSprite = m_iSpriteMin = 4;
	m_iSpriteMax = 9;
	m_rSrc.y = 256+128; // same row from the Player.png
	m_iDeathCtrMax = 5 * m_iFrameMax; // changes the speed 
									 // SpriteMax - SpriteMin = 5
}


Player::Player(SDL_Rect s, SDL_Rect d):AnimatedSprite(s,d)
{
	m_bGrounded = false;
	m_dAccelX = m_dAccelY = m_dVelX = m_dVelY = 0.0;
	m_dGrav = GRAV;
	m_dMaxAccelX = 2.0;
	m_dMaxVelX = 6.0;
	m_dMaxVelY = m_dGrav;
	m_dDrag = 0.925;
	m_iDir = 1;
	SetRunning(); // Initial state
}

void Player::SetDir(int dir)
{ // Will be used to set direction of sprite. Just added it for you.
	m_iDir = dir;
}

void Player::MoveX()
{
	m_dAccelX += 0.25 * m_iDir; // Change to speed var.
}

void Player::Update()
{
	m_dAccelX = min(max(m_dAccelX, -(m_dMaxAccelX)), (m_dMaxAccelX));
	m_dVelX = (m_dVelX + m_dAccelX) * m_dDrag;
	m_dVelX = min(max(m_dVelX, -(m_dMaxVelX)), (m_dMaxVelX));
	m_rDst.x += (int)m_dVelX;
	m_rDst.x = min(max(m_rDst.x, 0), 1024-128);
	m_dVelY += m_dAccelY + m_dGrav/8;
	m_dVelY = min(max(m_dVelY, -(m_dMaxVelY * 10)), (m_dMaxVelY));
	// Optional if you want platforms/hazards.
	if (fabs(m_dVelY > (m_dGrav / 4)))
		SetJumping();
	m_rDst.y += (int)m_dVelY;
	// m_rBound.x = m_rDst.x + 32
	// m_yBound.y = m_rDst.y +(m_state == rolling?64:4);
	Animate();
}

Obstacle::Obstacle(int x, bool b, SDL_Rect src, 
	SDL_Rect dst, bool p, bool r)
{
	m_iX = x;
	if (b) // Construct the Sprite
	{
		m_pSprite = new Sprite(src,dst);
		m_bIsPlatform = p;
		m_bRotates = r;
	}
}

Obstacle::~Obstacle()
{
	if (m_pSprite != nullptr)
	{
		delete m_pSprite;
		m_pSprite = nullptr;
	}
}