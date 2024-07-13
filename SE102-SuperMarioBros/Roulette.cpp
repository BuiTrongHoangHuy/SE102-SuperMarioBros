#include "Roulette.h"
#include "Mario.h"
#include "Mushroom.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Score.h"
#include "VirtualObject.h"
#include "Turtle.h"
#include "Leaf.h"
void CRoulette::Render()
{
	int aniID = ID_ANI_ROULETTE;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);

	//RenderBoundingBox();
}

void CRoulette::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ROULETTE_BBOX_WIDTH / 2;
	t = y - ROULETTE_BBOX_HEIGHT / 2;
	r = l + ROULETTE_BBOX_WIDTH;
	b = t + ROULETTE_BBOX_HEIGHT;
}
void CRoulette::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ROULETTE_STATE_CLOSED:
		ay = 0.0f;
		vy = 0.0f;
		break;
	}
}

void CRoulette::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

CRoulette::CRoulette(float x, float y) :CGameObject(x, y) {
	posX = x;
	posY = y;
	SetState(ROULETTE_STATE_CLOSED);
}

void CRoulette::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CRoulette*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{

	}

}
void CRoulette::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

