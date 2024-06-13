#pragma once
#include "GameObject.h"

#define LEAF_GRAVITY 0.002f
#define LEAF_WALKING_SPEED 0.05f

#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16

#define LEAF_DIE_TIMEOUT 500

#define LEAF_STATE_UP 100
#define LEAF_STATE_DOWN 200
#define LEAF_STATE_DIE 300

#define ID_ANI_LEAF 185000
#define ID_ANI_LEAF 185001


class CLeaf : public CGameObject
{
protected:
	float ax;
	float ay;
	float posY;
	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CLeaf(float x, float y);
	virtual void SetState(int state);
};