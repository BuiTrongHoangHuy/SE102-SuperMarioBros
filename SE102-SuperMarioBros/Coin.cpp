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
	if (dynamic_cast<CGift*>(e->obj)) {
		if (e->ny == -1) {
			this->Delete();
			
		}
	}
}

