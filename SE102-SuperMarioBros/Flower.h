#pragma once

#include "GameObject.h"

#define FLOWER_STATE_HIDDEN 0
#define FLOWER_STATE_APPEARING 1
#define FLOWER_STATE_VISIBLE 2
#define FLOWER_STATE_DISAPPEARING 3

#define FLOWER_APPEAR_SPEED 0.03f
#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 32
#define FLOWER_SHOOT_INTERVAL 2000 // 2 seconds

#define ID_ANI_FLOWER 165000
#define ID_ANI_FLOWER_APPEAR 165001
#define ID_ANI_FLOWER_APPEAR_LEFT_BOT 165001
#define ID_ANI_FLOWER_APPEAR_LEFT_TOP 165002
#define ID_ANI_FLOWER_APPEAR_RIGHT_BOT 165003
#define ID_ANI_FLOWER_APPEAR_RIGHT_TOP 165004

#define ID_ANI_FLOWER_READY_SHOOT_LEFT_BOT 165005
#define ID_ANI_FLOWER_READY_SHOOT_LEFT_TOP 165006
#define ID_ANI_FLOWER_READY_SHOOT_RIGHT_BOT 165007
#define ID_ANI_FLOWER_READY_SHOOT_RIGHT_TOP 165008

class CFlower : public CGameObject
{   
    float ay;
    float startY;
    float endY;
    DWORD lastShootTime;
    bool isHidden;
public:
    CFlower(float x, float y);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    virtual void SetState(int state);
    virtual int IsBlocking() { return 1; }	
    virtual int IsCollidable() { return 1; };

    void Shoot(float marioX, float marioY) ;
    int GetAniID();
};
