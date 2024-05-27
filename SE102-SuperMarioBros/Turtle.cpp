#include "TURTLE.h"

CTurtle::CTurtle(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = TURTLE_GRAVITY;
	die_start = -1;
	SetState(TURTLE_STATE_WALKING);
}

void CTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TURTLE_STATE_DIE)
	{
		left = x - TURTLE_BBOX_WIDTH / 2;
		top = y - TURTLE_BBOX_HEIGHT_DIE / 2;
		right = left + TURTLE_BBOX_WIDTH;
		bottom = top + TURTLE_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - TURTLE_BBOX_WIDTH / 2;
		top = y - TURTLE_BBOX_HEIGHT / 2;
		right = left + TURTLE_BBOX_WIDTH;
		bottom = top + TURTLE_BBOX_HEIGHT;
	}
}

void CTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CTurtle*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CTurtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == TURTLE_STATE_DIE) && (GetTickCount64() - die_start > TURTLE_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CTurtle::Render()
{
	int aniId = ID_ANI_TURTLE_WALKING;
	if (state == TURTLE_STATE_DIE)
	{
		aniId = ID_ANI_TURTLE_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CTurtle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TURTLE_STATE_DIE:
		die_start = GetTickCount64();
		y += (TURTLE_BBOX_HEIGHT - TURTLE_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case TURTLE_STATE_WALKING:
		vx = -TURTLE_WALKING_SPEED;
		break;
	}
}
int CTurtle:: GetAniId() {

}

