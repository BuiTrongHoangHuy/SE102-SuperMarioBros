#include "Fireball.h"
#include "Mario.h"
#include "PlayScene.h"

CFireball::CFireball(float x, float y, float directionX, float directionY) : CGameObject(x, y)
{
    this->direction = directionX;
    vx = directionX * FIREBALL_SPEED;
    vy = directionY * 0.03f;
}

void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt);
    x += vx * dt;
    y += vy * dt;
    CCollision::GetInstance()->Process(this, dt, coObjects); 
}

void CFireball::Render()
{
    CAnimations::GetInstance()->Get(ID_ANI_FIREBALL)->Render(x, y);
}

void CFireball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - FIREBALL_BBOX_WIDTH / 2;
    top = y - FIREBALL_BBOX_HEIGHT / 2;
    right = left + FIREBALL_BBOX_WIDTH;
    bottom = top + FIREBALL_BBOX_HEIGHT;
}

void CFireball::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!e->obj->IsBlocking()) return;
    this->Delete();
}
