#include "Leaf.h"
#include "debug.h"

CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = LEAF_GRAVITY;
	posY = y;
	die_start = -1;
	direction = 1;
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
	if (state == LEAF_STATE_UP && vy >= 0) {
		SetState(LEAF_STATE_DOWN);
	}
	if (state == LEAF_STATE_DOWN && vy <= 0) {
		direction = -direction;
		SetState(LEAF_STATE_DOWN);
		DebugOut(L"[INFO] ${dt} doi chieu!\n");
	}
	vector<LPGAMEOBJECT> coObjects2;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, &coObjects2);
}


void CLeaf::Render()
{
	int aniId = -1;
	if (direction > 0) {
		aniId = ID_ANI_LEAF_RIGHT;
	}
	else aniId = ID_ANI_LEAF;
	
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
		vy = -0.5f;
		ax = 0;
		ay = 0.002f;
		break;
	case LEAF_STATE_DOWN:
		if (direction>0) {
			vx = 0.0222f;
		}
		else vx = -0.0222f;
		ax = 0;
		vy = 0.03f;
		ay = -0.00002;
		break;

	case LEAF_STATE_DIE:
		vx = 0;
		vy = 0;
		ay = 0;
		isDeleted = true;
		break;

	}
}
