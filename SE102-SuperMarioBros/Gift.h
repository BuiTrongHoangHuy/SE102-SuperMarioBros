#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_GIFT 91000
#define ID_ANI_GIFTOPENED 96000

#define	GIFT_WIDTH 16
#define GIFT_BBOX_WIDTH 16
#define GIFT_BBOX_HEIGHT 16


class CGift : public CGameObject {
protected:
	bool isOpened = false;
public:
	CGift(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	int IsBlocking() { return 1; }
	virtual int IsCollidable() { return 1; };
	void Open() {
		if (isOpened == false) {
			isOpened = true;
		}
	}
};