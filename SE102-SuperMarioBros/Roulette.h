#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_ROULETTE 99001
#define ID_ANI_GIFTOPENED 96000

#define	ROULETTE_WIDTH 16
#define ROULETTE_BBOX_WIDTH 16
#define ROULETTE_BBOX_HEIGHT 16

#define ROULETTE_STATE_CLOSED 100
#define ROULETTE_STATE_OPENED 200
#define ROULETTE_STATE_PREOPENED 300
class CRoulette : public CGameObject {
protected:
	float ay;
	float posY;
	float posX;
public:
	CRoulette(float x, float y);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};