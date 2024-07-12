#include "Parakoopa.h"
#include "BackGroundObject.h"
#include "Gift.h"
#include "PlayScene.h"
#include "Paragoomba.h"

CParakoopa::CParakoopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PARAKOOPA_GRAVITY;
	die_start = -1;
	isOnPlatform = false;
	SetState(PARAKOOPA_STATE_WALKING);
	vobject = new CVirtualObject(x, y + PARAKOOPA_BBOX_HEIGHT / 2);
	preState = state;
}

void CParakoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARAKOOPA_STATE_DIE || state == PARAKOOPA_STATE_SPIN || state == PARAKOOPA_STATE_HEAL)
	{
		left = x - PARAKOOPA_BBOX_WIDTH / 2;
		top = y - PARAKOOPA_BBOX_HEIGHT_DIE / 2;
		right = left + PARAKOOPA_BBOX_WIDTH;
		bottom = top + PARAKOOPA_BBOX_HEIGHT_DIE;
	}
	else if (state == PARAKOOPA_STATE_READY_JUMP) {
		left = x - PARAKOOPA_READY_JUMP_BBOX_WIDTH / 2;
		top = y - PARAKOOPA_READY_JUMP_BBOX_HEIGHT / 2;
		right = left + PARAKOOPA_READY_JUMP_BBOX_WIDTH;
		bottom = top + PARAKOOPA_READY_JUMP_BBOX_HEIGHT;
	}

	else
	{
		left = x - PARAKOOPA_BBOX_WIDTH / 2;
		top = y - PARAKOOPA_BBOX_HEIGHT / 2;
		right = left + PARAKOOPA_BBOX_WIDTH;
		bottom = top + PARAKOOPA_BBOX_HEIGHT;
	}
}

void CParakoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParakoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CParakoopa*>(e->obj)) return;
	if (dynamic_cast<CBackGroundObject*>(e->obj)) return;
	if (dynamic_cast<CGift*>(e->obj)) {
		CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());
		CGift* gift = dynamic_cast<CGift*>(e->obj);
		if (e->nx != 0) {
			if (gift->GetState() == GIFT_STATE_CLOSED) {
				gift->SetState(GIFT_STATE_PREOPENED);
				if (gift->GetType() == 0) {
					mario->AddCoin();
				}
			}
		}
	}
	if (dynamic_cast<CGoomba*>(e->obj)) {
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		if (e->nx != 0) {
			goomba->SetState(GOOMBA_STATE_DIE);
		}
	}
	if (dynamic_cast<CParagoomba*>(e->obj)) {
		CParagoomba* paragoomba = dynamic_cast<CParagoomba*>(e->obj);
		if (state == TURTLE_STATE_SPIN) {

			if (e->nx != 0) {
				paragoomba->SetState(PARAGOOMBA_STATE_DIE);
			}
		}
	}
	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0)	isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (state == PARAKOOPA_STATE_JUMPING && isOnPlatform) {
		SetState(PARAKOOPA_STATE_WALKING);
	}
}

void CParakoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (state == PARAKOOPA_STATE_WALKING || state == PARAKOOPA_STATE_READY_JUMP) {
		SetState(PARAKOOPA_STATE_JUMPING);
	}
	if ((state == PARAKOOPA_STATE_DIE) && (GetTickCount64() - die_start > PARAKOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	isOnPlatform = false;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

int CParakoopa::GetAniId() {
	int aniID = -1;
		if (this->isOnPlatform) {
			if (vx >= 0)
				aniID = ID_ANI_PARAKOOPA_WALKING_RIGHT;
			else aniID = ID_ANI_PARAKOOPA_WALKING_LEFT;
		}
		else {
			if (vx >= 0)
				aniID = ID_ANI_PARAKOOPA_JUMP_RIGHT;
			else aniID = ID_ANI_PARAKOOPA_JUMP_LEFT;
		}
		if (state == TURTLE_STATE_SPIN) {
			aniID = ID_ANI_PARAKOOPA_SPIN;
		}
		if (state == TURTLE_STATE_HEAL) {
			aniID = ID_ANI_PARAKOOPA_HEAL;
		}
		if (state == TURTLE_STATE_SHELL) {
			aniID = ID_ANI_PARAKOOPA_DIE;
		}
		if (aniID == -1) aniID = ID_ANI_PARAKOOPA_IDLE;
	return aniID;
}
void CParakoopa::Render()
{
	int aniId = ID_ANI_PARAKOOPA_IDLE;
	if (state == PARAKOOPA_STATE_DIE)
	{
		aniId = ID_ANI_PARAKOOPA_DIE;
	}
	/*else if (state == PARAKOOPA_STATE_READY_JUMP) {
		aniId = ID_ANI_PARAKOOPA_READY_JUMP;
	}*/
	else if (state == PARAKOOPA_STATE_JUMPING) {
		if (vx >= 0)
			aniId = ID_ANI_PARAKOOPA_JUMP_RIGHT;
		else aniId = ID_ANI_PARAKOOPA_JUMP_LEFT;
	}
	else {
		aniId = GetAniId();
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CParakoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARAKOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (PARAKOOPA_BBOX_HEIGHT - PARAKOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARAKOOPA_STATE_WALKING:
		y -= (TURTLE_BBOX_HEIGHT - TURTLE_BBOX_HEIGHT_DIE) / 2;
		vx = -PARAKOOPA_WALKING_SPEED;
		ay = 0.02f;
		break;
	case PARAKOOPA_STATE_READY_JUMP:
		y -= (PARAKOOPA_READY_JUMP_BBOX_HEIGHT - PARAKOOPA_BBOX_HEIGHT) / 2;
		break;
	case PARAKOOPA_STATE_JUMPING:
		vy = -PARAKOOPA_JUMP_SPEED_Y;
		vx = -0.05f;
		ay = 0.001f;
		break;
	case PARAKOOPA_WINGLESS_STATE_WALKING:
		break;
	}
}

