#pragma once
#include "GameObject.h"

#define PARAGOOMBA_GRAVITY 0.002f
#define PARAGOOMBA_WALKING_SPEED 0.03f
#define PARAGOOMBA_JUMP_SPEED_Y 0.4f

#define PARAGOOMBA_BBOX_WIDTH 20
#define PARAGOOMBA_BBOX_HEIGHT 18
#define PARAGOOMBA_READY_JUMP_BBOX_WIDTH 20
#define PARAGOOMBA_READY_JUMP_BBOX_HEIGHT 24
#define PARAGOOMBA_BBOX_HEIGHT_DIE 7

#define PARAGOOMBA_DIE_TIMEOUT 500

#define PARAGOOMBA_STATE_WALKING 100
#define PARAGOOMBA_STATE_READY_JUMP	200
#define PARAGOOMBA_STATE_JUMPING 300
#define PARAGOOMBA_WINGLESS_STATE_WALKING 400
#define PARAGOOMBA_STATE_DIE 500

#define PARAGOOMBA_JUMP_INTERVAL 100
#define ID_ANI_PARAGOOMBA_WALKING 195000
#define ID_ANI_PARAGOOMBA_WINGLESS_WALKING 195001
#define ID_ANI_PARAGOOMBA_DIE 195002
#define ID_ANI_PARAGOOMBA_READY_JUMP 195003
#define ID_ANI_PARAGOOMBA_JUMPING 195004

class CParagoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	int stepCount;
	ULONGLONG die_start;
	BOOLEAN isOnPlatform;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CParagoomba(float x, float y);
	virtual void SetState(int state);
};