#include "VirtualObject.h"

CVirtualObject:: CVirtualObject(float x, float y) : CGameObject(x, y)
{
    vx = 0;
    vy = 0;
    //isOnPlatform = false;
}

void CVirtualObject::Render() {
	RenderBoundingBox();
}

void CVirtualObject:: GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x -1;
    top = y-1;
    right = x + 1;
    bottom = y + 1;
}

int CVirtualObject::IsCollidable() { return 1; }
int CVirtualObject::IsBlocking()  { return 0; }

void CVirtualObject::OnNoCollision(DWORD dt)
{
    y += vy * dt;
    x += vx * dt;    
	isOnPlatform = false;

}

void CVirtualObject::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CVirtualObject*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
	}
}
BOOLEAN CVirtualObject::GetIsOnPlatform() {
	return this->isOnPlatform;
}
void CVirtualObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
	//isOnPlatform = false;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
