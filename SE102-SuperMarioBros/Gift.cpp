#include "Gift.h"
#include "Mario.h"
#include "Mushroom.h"
#include "PlayScene.h"
#include "Coin.h"
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
		ay = 0.0f;
		vy = 0.0f;
		break;
	case GIFT_STATE_PREOPENED:
		ay = 0.002f;
		vy = -0.25f;
		break;
	case GIFT_STATE_OPENED:
		ay = 0; 
		vy = 0;
		break;
	}
	
}

void CGift::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);


	if (state == GIFT_STATE_PREOPENED) {
		vy += ay * dt;
		y += vy * dt;
	}
	if (y >= minHeight && state == GIFT_STATE_PREOPENED) {
		ay = 0;
		vy = 0;
		y = minHeight;
		SetState(GIFT_STATE_OPENED);
		OpenGift();
	}
}

CGift::CGift(float x, float y, int typeGift) :CGameObject(x, y) {
	this->ay = 0.000f;
	maxHeight = y - 15;
	minHeight = y;
	this->typeGift = typeGift;
	SetState(GIFT_STATE_CLOSED);
}

void CGift::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMario*>(e->obj) != nullptr) {
		if (state == GIFT_STATE_CLOSED) {
			SetState(GIFT_STATE_PREOPENED);
		}
	}
}
void CGift::OnNoCollision(DWORD dt)
{
	/*x += vx * dt;
	y += vy * dt;*/
}

void CGift::OpenGift() {
	if (this->typeGift == 1) {
		LPGAMEOBJECT mushroom = new CMushroom(x, y);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		if (this != nullptr) {
			p->AddFowardNewObject(mushroom,this );
		}
	}
	else {
		LPGAMEOBJECT coin = new CCoin(x, y, 1);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		if (this != nullptr) {
			p->AddFowardNewObject(coin, this);
		}
	}
}

int CGift::GetType() {
	return this->typeGift;
}