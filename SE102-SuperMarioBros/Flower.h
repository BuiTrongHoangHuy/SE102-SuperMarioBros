#pragma once

#include "GameObject.h"

#define FLOWER_STATE_HIDDEN 0
#define FLOWER_STATE_APPEARING 1
#define FLOWER_STATE_VISIBLE 2
#define FLOWER_STATE_DISAPPEARING 3

#define FLOWER_APPEAR_SPEED 0.025f
#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 32
#define FLOWER_GREEN_BBOX_HEIGHT 22
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

#define ID_ANI_GREEN_FLOWER_NO_SHOOT 166000

#define ID_ANI_GREEN_FLOWER_APPEAR 165011
#define ID_ANI_GREEN_FLOWER_APPEAR_LEFT_BOT 165011
#define ID_ANI_GREEN_FLOWER_APPEAR_LEFT_TOP 165012
#define ID_ANI_GREEN_FLOWER_APPEAR_RIGHT_BOT 165013
#define ID_ANI_GREEN_FLOWER_APPEAR_RIGHT_TOP 165014
#define ID_ANI_GREEN_FLOWER_READY_SHOOT_LEFT_BOT 165015
#define ID_ANI_GREEN_FLOWER_READY_SHOOT_LEFT_TOP 165016
#define ID_ANI_GREEN_FLOWER_READY_SHOOT_RIGHT_BOT 165017
#define ID_ANI_GREEN_FLOWER_READY_SHOOT_RIGHT_TOP 165018
#define TYPE_FLOWER_SHOOT  1
#define TYPE_GREEN_FLOWER_NO_SHOOT  2
#define TYPE_GREEN_FLOWER_SHOOT  3
class CFlower : public CGameObject
{   
    float ay;
    float startY;
    float endY;
    DWORD lastShootTime;
    bool isHidden;
    int type;
public:
    CFlower(float x, float y,int type);
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
