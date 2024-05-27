#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define SCORE_WIDTH 30
#define SCORE_BBOX_WIDTH 12
#define SCORE_BBOX_HEIGHT 8
#define ID_SPIRTE_SCORE 45000
class CScore : public CGameObject {
public:
	CScore(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};