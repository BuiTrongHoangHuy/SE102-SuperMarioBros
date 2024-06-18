#pragma once
#include "GameObject.h"
#include "VirtualObject.h"
#define TURTLE_GRAVITY 0.002f
#define TURTLE_WALKING_SPEED 0.05f


#define TURTLE_BBOX_WIDTH 16
#define TURTLE_BBOX_HEIGHT 26
#define TURTLE_BBOX_HEIGHT_DIE 16

#define TURTLE_DIE_TIMEOUT 5000

#define TURTLE_STATE_WALKING 100
#define TURTLE_STATE_DIE 200
#define TURTLE_STATE_SPIN 300
#define TURTLE_STATE_HEAL 400
#define TURTLE_STATE_SHELL 500


#define ID_ANI_TURTLE_WALKING_LEFT 155000
#define ID_ANI_TURTLE_WALKING_RIGHT 155001
#define ID_ANI_TURTLE_DIE 155002
#define ID_ANI_TURTLE_IDLE 155003
#define ID_ANI_TURTLE_SPIN 155004
#define ID_ANI_TURTLE_HEAL 155005

class CTurtle : public CGameObject
{
protected:
	float ax;
	float ay;
	BOOLEAN isOnPlatform;

	CVirtualObject* vobject;
	ULONGLONG die_start;
	ULONGLONG check;
	int preState;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int GetAniId();


public:
	CTurtle(float x, float y);
	virtual void SetState(int state);
};