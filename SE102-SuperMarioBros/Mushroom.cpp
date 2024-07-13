#include "MUSHROOM.h"

CMushroom::CMushroom(float x, float y,int type) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = MUSHROOM_GRAVITY;
	this->type = type;
	posY = y;
	die_start = -1;
	SetState(MUSHROOM_STATE_APPEAR);
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x - MUSHROOM_BBOX_WIDTH / 2 ;
		top = y - MUSHROOM_BBOX_HEIGHT / 2;
		right = left + MUSHROOM_BBOX_WIDTH ;
		bottom = top + MUSHROOM_BBOX_HEIGHT -1;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		
	}
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (state == MUSHROOM_STATE_APPEAR && y<posY-16) {
		SetState(MUSHROOM_STATE_WALKING);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CMushroom::Render()
{
	int aniId = -1;
	if (type == 1) {
		aniId = ID_ANI_MUSHROOM;
	}
	else if (type == 2) {
		aniId = ID_ANI_GREEN_MUSHROOM;
	}

	//CSprites* m = CSprites::GetInstance();
	//m->Get(ID_ANI_MUSHROOM)->Draw(x, y);
	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_APPEAR:
		vx = 0;
		vy = -0.015f;
		ay = 0;
		break;
	case MUSHROOM_STATE_WALKING:
		vx = -0.04f;
		vy = 0;
		ay = 0.002f;
		break;

	case MUSHROOM_STATE_EATEN:
		vx = 0;
		vy = 0;
		ay = 0;
		isDeleted = true;
		break;

	}
}
