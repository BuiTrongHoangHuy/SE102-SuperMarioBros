#pragma once
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f
		
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16
		
#define MUSHROOM_DIE_TIMEOUT 500
		
#define MUSHROOM_STATE_APPEAR 100
#define MUSHROOM_STATE_WALKING 200
#define MUSHROOM_STATE_EATEN 300

#define ID_ANI_MUSHROOM 145000
#define ID_ANI_GREEN_MUSHROOM 145001


class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	float posY;
	ULONGLONG die_start;
	int type;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom(float x, float y,int type);
	virtual void SetState(int state);
};