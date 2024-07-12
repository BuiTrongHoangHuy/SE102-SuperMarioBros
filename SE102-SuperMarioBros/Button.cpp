#include "Button.h"
#include "PlayScene.h"

CButton::CButton(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = BUTTON_GRAVITY;
	die_start = -1;
	SetState(BUTTON_STATE_WALKING);
}

void CButton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == BUTTON_STATE_DIE)
	{
		left = x - BUTTON_BBOX_WIDTH / 2;
		top = y - BUTTON_BBOX_HEIGHT_DIE / 2;
		right = left + BUTTON_BBOX_WIDTH;
		bottom = top + BUTTON_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - BUTTON_BBOX_WIDTH / 2;
		top = y - BUTTON_BBOX_HEIGHT / 2;
		right = left + BUTTON_BBOX_WIDTH - 1;
		bottom = top + BUTTON_BBOX_HEIGHT - 1;
	}
}

void CButton::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CButton::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CButton*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == BUTTON_STATE_DIE) && (GetTickCount64() - die_start > BUTTON_DIE_TIMEOUT)&&isClick)
	{

		//isDeleted = true;
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		p->ChangeCoin();
		isClick = false;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CButton::Render()
{
	int aniId = ID_ANI_BUTTON_WALKING;
	if (state == BUTTON_STATE_DIE)
	{
		aniId = ID_ANI_BUTTON_DIE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CButton::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BUTTON_STATE_DIE:
		die_start = GetTickCount64();
		isClick = true;
		y += (BUTTON_BBOX_HEIGHT - BUTTON_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case BUTTON_STATE_WALKING:
		vx = 0;
		break;
	}
}
