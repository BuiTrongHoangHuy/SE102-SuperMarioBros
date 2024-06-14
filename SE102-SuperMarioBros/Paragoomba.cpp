#include "Paragoomba.h"
#include "BackGroundObject.h"

CParagoomba::CParagoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PARAGOOMBA_GRAVITY;
	die_start = -1;
	isOnPlatform = false;
	SetState(PARAGOOMBA_STATE_WALKING);
}

void CParagoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARAGOOMBA_STATE_DIE)
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (state == PARAGOOMBA_STATE_READY_JUMP) {
		left = x - PARAGOOMBA_READY_JUMP_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_READY_JUMP_BBOX_HEIGHT / 2 ;
		right = left + PARAGOOMBA_READY_JUMP_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_READY_JUMP_BBOX_HEIGHT ;
	}
	else
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH ;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT ;
	}
}

void CParagoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParagoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CParagoomba*>(e->obj)) return;
	if (dynamic_cast<CBackGroundObject*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0)	isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (state == PARAGOOMBA_STATE_JUMPING && isOnPlatform) {
		SetState(PARAGOOMBA_STATE_WALKING);
	}
}

void CParagoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (state == PARAGOOMBA_STATE_WALKING || state ==PARAGOOMBA_STATE_READY_JUMP) {
		stepCount++;
		if (stepCount >= PARAGOOMBA_JUMP_INTERVAL) {
			SetState(PARAGOOMBA_STATE_READY_JUMP);
		}
		if (stepCount >= 1.5 * PARAGOOMBA_JUMP_INTERVAL) {
			SetState(PARAGOOMBA_STATE_JUMPING);
			stepCount = 0;
		}
	}
	if ((state == PARAGOOMBA_STATE_DIE) && (GetTickCount64() - die_start > PARAGOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	isOnPlatform = false;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CParagoomba::Render()
{
	int aniId = ID_ANI_PARAGOOMBA_WALKING;
	if (state == PARAGOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_PARAGOOMBA_DIE;
	}
	else if (state == PARAGOOMBA_STATE_READY_JUMP) {
		aniId = ID_ANI_PARAGOOMBA_READY_JUMP;
	}
	else if (state == PARAGOOMBA_STATE_JUMPING) {
		aniId = ID_ANI_PARAGOOMBA_JUMPING;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CParagoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARAGOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (PARAGOOMBA_BBOX_HEIGHT - PARAGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARAGOOMBA_STATE_WALKING:
		vx = -PARAGOOMBA_WALKING_SPEED ;
		break;
	case PARAGOOMBA_STATE_READY_JUMP:
		y -= (PARAGOOMBA_READY_JUMP_BBOX_HEIGHT - PARAGOOMBA_BBOX_HEIGHT) / 2;
		break;
	case PARAGOOMBA_STATE_JUMPING:	
		vy = -PARAGOOMBA_JUMP_SPEED_Y;
		vx = -0.05f;
		ay = 0.0015f;
		break;
	}
}
