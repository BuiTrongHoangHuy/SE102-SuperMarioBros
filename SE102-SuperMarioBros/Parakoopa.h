#pragma once
#include "GameObject.h"

#define PARAKOOPA_GRAVITY 0.002f
#define PARAKOOPA_WALKING_SPEED 0.03f
#define PARAKOOPA_JUMP_SPEED_Y 0.3f

#define PARAKOOPA_BBOX_WIDTH 20
#define PARAKOOPA_BBOX_HEIGHT 18
#define PARAKOOPA_READY_JUMP_BBOX_WIDTH 20
#define PARAKOOPA_READY_JUMP_BBOX_HEIGHT 24
#define PARAKOOPA_BBOX_HEIGHT_DIE 7
#define PARAKOOPA_WINGLESS_BBOX_WIDTH 16
#define PARAKOOPA_WINGLESS_BBOX_HEIGHT 14
#define PARAKOOPA_DIE_TIMEOUT 500

#define PARAKOOPA_STATE_WALKING 100
#define PARAKOOPA_STATE_READY_JUMP	200
#define PARAKOOPA_STATE_JUMPING 300
#define PARAKOOPA_WINGLESS_STATE_WALKING 400
#define PARAKOOPA_STATE_DIE 500

#define PARAKOOPA_JUMP_INTERVAL 100
#define ID_ANI_PARAKOOPA_WALKING 195000
#define ID_ANI_PARAKOOPA_WINGLESS_WALKING 195001
#define ID_ANI_PARAKOOPA_DIE 195002
#define ID_ANI_PARAKOOPA_READY_JUMP 195003
#define ID_ANI_PARAKOOPA_JUMPING 195004

class CParakoopa : public CGameObject
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
	CParakoopa(float x, float y);
	virtual void SetState(int state);
};