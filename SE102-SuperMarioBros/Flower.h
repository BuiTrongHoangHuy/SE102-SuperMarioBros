#pragma once

#include "GameObject.h"

#define FLOWER_STATE_HIDDEN 0
#define FLOWER_STATE_APPEARING 1
#define FLOWER_STATE_VISIBLE 2
#define FLOWER_STATE_DISAPPEARING 3

#define FLOWER_APPEAR_SPEED 0.05f
#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 32

class CFlower : public CGameObject
{
    float startY;
    float endY;
public:
    CFlower(float x, float y);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
