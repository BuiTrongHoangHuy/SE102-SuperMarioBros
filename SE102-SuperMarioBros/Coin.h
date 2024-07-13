#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

#define COIN_TYPE_FIXED 0
#define COIN_TYPE_FROMGIFT 1
#define COIN_STATE_FIXED 100
#define COIN_STATE_FROMGIFT 200
class CCoin : public CGameObject {
protected:
	float ay;
	float posY;
	float posX;
	int typeCoin;
public:
	CCoin(float x, float y,int typeCoin);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int GetTypeCoin(){
		return typeCoin;
	}
};