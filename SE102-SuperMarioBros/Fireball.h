#pragma once

#include "GameObject.h"

#define FIREBALL_SPEED 0.2f
#define FIREBALL_BBOX_WIDTH 8
#define FIREBALL_BBOX_HEIGHT 8

class CFireball : public CGameObject
{
    int direction;
public:
    CFireball(float x, float y, int direction);

    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};
