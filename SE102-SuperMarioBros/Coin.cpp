#include "Coin.h"
#include "Gift.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}
void CCoin:: OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}
void CCoin:: OnCollisionWith(LPCOLLISIONEVENT e) {
	//CGift* gift = dynamic_cast<CGift*>(e->obj);
	//if (dynamic_cast<CGift*>(e->obj)) {
	//	if (e->ny == -1) {
	//		this->Delete();
	//	}
	//}
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CCoin*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{

	}
}
CCoin::CCoin(float x, float y,int typeCoin) :CGameObject(x, y)
{
	this->posY = y;
	this->typeCoin = typeCoin;
	if (this->typeCoin == COIN_TYPE_FROMGIFT) {
		SetState(COIN_STATE_FROMGIFT);
	}
	else SetState(COIN_STATE_FIXED);
}
void CCoin::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_STATE_FROMGIFT:
		vy = -0.5f;
		ay = 0.002f;
		break;
	case COIN_STATE_FIXED:
		vy = 0;
		ay = 0;
		break;
	}
}
void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	if (state == COIN_STATE_FROMGIFT) {
		vy += ay * dt;
		if (y >= posY) {
			this->Delete();
			isDeleted = true;
		}
	}
}
