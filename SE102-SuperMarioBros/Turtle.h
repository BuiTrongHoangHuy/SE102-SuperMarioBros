#pragma once
#include "GameObject.h"
#include "VirtualObject.h"
#define TURTLE_GRAVITY 0.002f
#define TURTLE_WALKING_SPEED 0.01f


#define TURTLE_BBOX_WIDTH 16
#define TURTLE_BBOX_HEIGHT 26
#define TURTLE_BBOX_HEIGHT_DIE 16

#define TURTLE_DIE_TIMEOUT 500

#define TURTLE_STATE_WALKING 100
#define TURTLE_STATE_DIE 200

#define ID_ANI_TURTLE_IDLE 155003

#define ID_ANI_TURTLE_WALKING_LEFT 155000
#define ID_ANI_TURTLE_WALKING_RIGHT 155001
#define ID_ANI_TURTLE_DIE 155002

class CTurtle : public CGameObject
{
protected:
	float ax;
	float ay;
	BOOLEAN isOnPlatform;

	CVirtualObject* vobject;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int GetAniId();


public:
	CTurtle(float x, float y);
	virtual void SetState(int state);
};