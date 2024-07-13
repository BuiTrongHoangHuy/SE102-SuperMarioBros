#pragma once
#include "GameObject.h"

#define BUTTON_GRAVITY 0.002f
#define BUTTON_WALKING_SPEED 0.05f


#define BUTTON_BBOX_WIDTH 16
#define BUTTON_BBOX_HEIGHT 14
#define BUTTON_BBOX_HEIGHT_DIE 7

#define BUTTON_DIE_TIMEOUT 500
#define BUTTON_RESPAWN_TIMEOUT 5000

#define BUTTON_STATE_WALKING 100
#define BUTTON_STATE_DIE 200

#define ID_ANI_BUTTON_WALKING 195005
#define ID_ANI_BUTTON_DIE 195006

class CButton : public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG die_start;
	ULONGLONG timeRespawn;
	BOOLEAN isClick = true;
	BOOLEAN isRespawn = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CButton(float x, float y);
	virtual void SetState(int state);
};