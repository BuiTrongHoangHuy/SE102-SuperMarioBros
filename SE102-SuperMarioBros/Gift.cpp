#include "Gift.h"

void CGift::Render()
{
	int aniID = ID_ANI_GIFT;
	if (isOpened) {
		aniID = ID_ANI_GIFTOPENED;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);

	//RenderBoundingBox();
}

void CGift::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GIFT_BBOX_WIDTH / 2;
	t = y - GIFT_BBOX_HEIGHT / 2;
	r = l + GIFT_BBOX_WIDTH	;
	b = t + GIFT_BBOX_HEIGHT ;
}
void CGift::SetState(int state)
{
	CGameObject::SetState(state);
}

void CGift::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy = ay * dt;
	if (state == GIFT_STATE_OPENED)
	{

	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
CGift::CGift(float x, float y) :CGameObject(x, y) {
	this->ay = 0.002f;
	SetState(GIFT_STATE_CLOSED);
}