#pragma once

#include "GameObject.h"

#define FLOWER_STATE_HIDDEN 0
#define FLOWER_STATE_APPEARING 1
#define FLOWER_STATE_VISIBLE 2
#define FLOWER_STATE_DISAPPEARING 3

#define FLOWER_APPEAR_SPEED 0.015f
#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 32

#define ID_ANI_FLOWER 165000
#define ID_ANI_FLOWER_APPEAR 165001

class CFlower : public CGameObject
{   
    float ay;
    float startY;
    float endY;
    DWORD lastShootTime;
public:
    CFlower(float x, float y);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    virtual void SetState(int state);
    virtual int IsBlocking() { return 0; }
    void Shoot(float marioX, float marioY) {};
};
