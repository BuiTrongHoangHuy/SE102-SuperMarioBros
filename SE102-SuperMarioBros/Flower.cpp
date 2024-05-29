#include "Flower.h"
#include "Animations.h"

CFlower::CFlower(float x, float y) : CGameObject(x, y)
{
    this->startY = y;
    this->endY = y - FLOWER_BBOX_HEIGHT;
    this->state = FLOWER_STATE_HIDDEN;
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
    CGameObject::Update(dt);

    switch (state)
    {
    case FLOWER_STATE_APPEARING:
        y -= FLOWER_APPEAR_SPEED * dt;
        if (y <= endY) {
            y = endY;
            SetState(FLOWER_STATE_VISIBLE);
        }
        break;
    case FLOWER_STATE_DISAPPEARING:
        y += FLOWER_APPEAR_SPEED * dt;
        if (y >= startY) {
            y = startY;
            SetState(FLOWER_STATE_HIDDEN);
        }
        break;
    }
}

void CFlower::Render()
{
    if (state != FLOWER_STATE_HIDDEN) {
         //CAnimations::GetInstance()->Get(ID_ANI_FLOWER)->Render(x, y);
    }
}
