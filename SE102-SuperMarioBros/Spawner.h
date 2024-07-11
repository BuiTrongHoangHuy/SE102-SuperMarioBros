#pragma once
#include "GameObject.h"

class CSpawner : public CGameObject
{
protected:


public:
    CSpawner(float x, float y, int type)
        : CGameObject(x, y) {}

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
    void Render() override;

    int IsCollidable() { return 1; }
    int IsBlocking() { return 0; }

    //void OnCollisionWith(LPCOLLISIONEVENT e);
};