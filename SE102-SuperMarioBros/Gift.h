#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_GIFT 91000
#define ID_ANI_GIFTOPENED 96000

#define	GIFT_WIDTH 16
#define GIFT_BBOX_WIDTH 16
#define GIFT_BBOX_HEIGHT 16

#define GIFT_STATE_CLOSED 100
#define GIFT_STATE_OPENED 200

class CGift : public CGameObject {
protected:
	bool isOpened = false;
	float ay;
public:
	CGift(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e); 
	virtual int IsCollidable() { return 1; };
	void Open() {
		if (isOpened == false) {
			isOpened = true;
		}
	}
	virtual void SetState(int state);
};