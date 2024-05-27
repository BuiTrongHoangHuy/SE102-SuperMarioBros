#include "Gift.h"
#include "Mario.h"

void CGift::Render()
{
	int aniID = ID_ANI_GIFT;
	if (state == GIFT_STATE_OPENED) {
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
	switch (state)
	{
	case GIFT_STATE_CLOSED:
		ay = 0.0f; // No gravity when closed
		vy = 0.0f;
		break;
	case GIFT_STATE_PREOPENED:
		ay = 0.002f;
		vy = -0.25f;
		break;
	case GIFT_STATE_OPENED:
		ay = 0; // Apply gravity when opened
		break;
	}
	
}

void CGift::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == GIFT_STATE_PREOPENED) {
		vy += ay * dt;
		y += vy * dt;
	}
	if (y >= minHeight && state == GIFT_STATE_PREOPENED) {
		ay = 0;
		vy = 0;
		y = minHeight;
		SetState(GIFT_STATE_OPENED);
	}
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

CGift::CGift(float x, float y) :CGameObject(x, y) {
	this->ay = 0.000f;
	maxHeight = y - 15;
	minHeight = y;
	SetState(GIFT_STATE_CLOSED);
}

