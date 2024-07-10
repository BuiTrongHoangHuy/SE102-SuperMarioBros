#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_BRICK_LINE	10001
#define ID_ANI_BRICK_GLASS	10002
#define ID_ANI_BRICK_HIDDEN	10003
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
	int type;
public:
	CBrick(float x, float y, int type) : CGameObject(x, y) {
		this->type = type;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};