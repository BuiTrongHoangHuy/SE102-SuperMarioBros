#include "Flower.h"
#include "Animations.h"
#include "debug.h"

CFlower::CFlower(float x, float y) : CGameObject(x, y)
{
    ay = 0.002f;
    this->x = x;
    this->y = y;
    this->startY = y;
    this->endY = y - FLOWER_BBOX_HEIGHT;
    SetState(FLOWER_STATE_APPEARING);
    lastShootTime = 0;
}

void CFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - FLOWER_BBOX_WIDTH / 2;
    top = y - FLOWER_BBOX_HEIGHT / 2;
    right = left + FLOWER_BBOX_WIDTH;
    bottom = top + FLOWER_BBOX_HEIGHT;
}
void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    //vy += ay * dt;

    if (state == FLOWER_STATE_APPEARING) {
        if (y <= endY) {
            y = endY;
            SetState(FLOWER_STATE_DISAPPEARING); 
            DebugOut(L">>> hehe >>> \n" );

        }
    } else if (state == FLOWER_STATE_DISAPPEARING) {
        if (y >= startY) {
            y = startY;
            SetState(FLOWER_STATE_APPEARING);
        }
    }
    CGameObject::Update(dt);
    CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CFlower::Render()
{
    if (state != FLOWER_STATE_HIDDEN) {
         CAnimations::GetInstance()->Get(ID_ANI_FLOWER_APPEAR)->Render(x, y);
    }
}
void CFlower::OnNoCollision(DWORD dt) {
    x += vx * dt;
    y += vy * dt;
}
void CFlower::OnCollisionWith(LPCOLLISIONEVENT e) {
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CFlower*>(e->obj)) return;

    if (e->ny != 0)
    {
        vy = 0;
    }
    else if (e->nx != 0)
    {
    }
}
void CFlower::SetState(int state) {
    CGameObject::SetState(state);

    switch (state)
    {
    case FLOWER_STATE_APPEARING:
        vy = -FLOWER_APPEAR_SPEED;
        break;
    case FLOWER_STATE_DISAPPEARING:
        vy = FLOWER_APPEAR_SPEED;
        break;
    default:
        break;
    }

}