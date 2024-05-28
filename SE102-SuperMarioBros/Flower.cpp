#include "Flower.h"
#include "Animations.h"

CFlower::CFlower(float x, float y) : CGameObject(x, y)
{
    this->startY = y;
    this->endY = y - FLOWER_BBOX_HEIGHT;
    this->state = FLOWER_STATE_HIDDEN;
}


