#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"
#include "Mario.h"
#define ID_ANI_PIPE 125000
#define PIPE_WIDTH 30
#define PIPE_BBOX_WIDTH 30
#define PIPE_BBOX_HEIGHT 48
//#define PIPE_BBOX_HEIGHT 150

class CPipe : public CGameObject {
public:
	bool check=true;
	CPipe(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	int IsCollidable() { return 0; };
	

};