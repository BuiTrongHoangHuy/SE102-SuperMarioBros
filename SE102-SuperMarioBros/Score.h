#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define SCORE_WIDTH 12
#define SCORE_BBOX_WIDTH 12
#define SCORE_BBOX_HEIGHT 8
#define ID_SPIRTE_SCORE 45000
#define ID_ANI_SCORE 45100
class CScore : public CGameObject {
protected:
	float ay;
public:
	CScore(float x, float y);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};