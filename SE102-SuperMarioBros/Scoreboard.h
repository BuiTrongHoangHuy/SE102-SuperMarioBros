#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
#define ID_ANI_SCOREBOARD 63002
class CScoreboard
{
protected:
	/*float Width;
	float Height;
	int spriteId;*/
	int score;
	int lives;
	int coins;
	int timeLeft;
	int world;
	int level;

public:
	CScoreboard()
	{
		score = 0;
		lives = 3;
		coins = 0;
		timeLeft = 300; 
		world = 1;
		level = 1;
	}

	int IsDirectionColliable(float nx, float ny);
	virtual int IsBlocking() { return 0; }
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};

