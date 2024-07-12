#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_BRICK_LINE	10001
#define ID_ANI_BRICK_GLASS	10002
#define ID_ANI_BRICK_HIDDEN	10003
#define ID_ANI_BRICK_BUTTON	10004
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_WALKING 100
#define BRICK_STATE_DIE 200
#define BRICK_DIE_TIMEOUT 500
class CBrick : public CGameObject {
	int isButton;
	ULONGLONG die_start;

public:
	int type;
	CBrick(float x, float y, int type,int isButton) : CGameObject(x, y) {
		this->type = type;
		this->isButton = isButton;
		die_start = -1;

	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);

};