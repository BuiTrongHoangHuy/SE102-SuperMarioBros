#include "Leaf.h"

CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = LEAF_GRAVITY;
	posY = y;
	die_start = -1;
	SetState(LEAF_STATE_UP);
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LEAF_BBOX_WIDTH / 2;
	top = y - LEAF_BBOX_HEIGHT / 2;
	right = left + LEAF_BBOX_WIDTH;
	bottom = top + LEAF_BBOX_HEIGHT - 1;
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CLeaf*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{

	}
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (state == LEAF_STATE_UP && y < posY - 16) {
		SetState(LEAF_STATE_DOWN);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CLeaf::Render()
{
	int aniId = ID_ANI_LEAF;

	//CSprites* m = CSprites::GetInstance();
	//m->Get(ID_ANI_LEAF)->Draw(x, y);
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_UP:
		vx = 0;
		vy = -0.015f;
		ay = 0;
		break;
	case LEAF_STATE_DOWN:
		vx = -0.04f;
		vy = 0;
		ay = 0.002f;
		break;

	case LEAF_STATE_DIE:
		vx = 0;
		vy = 0;
		ay = 0;
		isDeleted = true;
		break;

	}
}
