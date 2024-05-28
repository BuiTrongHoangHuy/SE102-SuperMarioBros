#pragma once

#include "GameObject.h"

class CVirtualObject : public CGameObject
{
protected:
    BOOLEAN isOnPlatform=true;
    float ay =0.002f;
public:
    CVirtualObject(float x, float y);

    void Render();
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    int IsCollidable();
    int IsBlocking();
    void OnNoCollision(DWORD dt);
    void OnCollisionWith(LPCOLLISIONEVENT e);
    BOOLEAN GetIsOnPlatform();
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

};
