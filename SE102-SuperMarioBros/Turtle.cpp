#include "Turtle.h"
#include "VirtualObject.h"
#include "PlayScene.h"
#include "Gift.h"
#include "Goomba.h"
#include "Paragoomba.h"
CTurtle::CTurtle(float x, float y,int type) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = TURTLE_GRAVITY;
	this->type = type;
	isOnPlatform = false;
	die_start = -1;
	vobject = new CVirtualObject(x, y + TURTLE_BBOX_HEIGHT / 2 );
	SetState(TURTLE_STATE_WALKING);
	preState = state;
}

void CTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == TURTLE_STATE_DIE||state==TURTLE_STATE_SPIN||state == TURTLE_STATE_HEAL)
	{
		left = x - TURTLE_BBOX_WIDTH / 2;
		top = y - TURTLE_BBOX_HEIGHT_DIE / 2;
		right = left + TURTLE_BBOX_WIDTH;
		bottom = top + TURTLE_BBOX_HEIGHT_DIE -1;
	}
	else
	{
		left = x - TURTLE_BBOX_WIDTH / 2;
		top = y - TURTLE_BBOX_HEIGHT / 2;
		right = left + TURTLE_BBOX_WIDTH;
		bottom = top + TURTLE_BBOX_HEIGHT -1;
	}
}

void CTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CTurtle*>(e->obj)) return;
	if (dynamic_cast<CGift*>(e->obj)) {
		if (state == TURTLE_STATE_SPIN) {

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
	}
	if (dynamic_cast<CGoomba*>(e->obj)) {
		if (state == TURTLE_STATE_SPIN) {

		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		if (e->nx != 0) {
			goomba->SetState(GOOMBA_STATE_DIE);
			e->obj->SetSpeed(0, -0.3f);

		}
		}
	}
	if (dynamic_cast<CParagoomba*>(e->obj)) {

		CParagoomba* paragoomba = dynamic_cast<CParagoomba*>(e->obj);
		if (state == TURTLE_STATE_SPIN) {

			if (e->nx != 0) {
				paragoomba->SetState(PARAGOOMBA_STATE_DIE);
				e->obj->SetSpeed(0, -0.3f);

			}
		}
		
	}
	if (dynamic_cast<CBrick*>(e->obj)) {
		if (state == TURTLE_STATE_SPIN) {
			CBrick* brick = dynamic_cast<CBrick*>(e->obj);
			if (e->nx!=0&&brick->type==2) {
				brick->SetState(BRICK_STATE_DIE);
			}
		}
	}
	if (!e->obj->IsBlocking()) return;
	if (e->ny != 0)
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
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
	if (preState != state) {
		preState = state;
		DebugOut(L"[INFO] KeyUp: %d\n", state);
	}
	if (((state == TURTLE_STATE_DIE) || (state == TURTLE_STATE_SHELL)) && (GetTickCount64() - die_start > TURTLE_DIE_TIMEOUT))
	{
		
		check = GetTickCount64();
		SetState(TURTLE_STATE_HEAL);
		//isDeleted = true;
		//return;
	}
	if (state== TURTLE_STATE_HEAL && GetTickCount64() - check > 3000) {
		die_start = -1;
		SetState(TURTLE_STATE_WALKING);
		CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());
		mario->SetIsHold(FALSE);
	}
	if (state == TURTLE_STATE_DIE) {
		if (vx > 0) {
			this->vobject->SetPosition(x + 5, y + TURTLE_BBOX_HEIGHT_DIE / 2 - 2);
		}
		else
			this->vobject->SetPosition(x - 5, y + TURTLE_BBOX_HEIGHT_DIE / 2 - 2);
	}
	else {

		if (vx > 0) {
			this->vobject->SetPosition( x+5, y + TURTLE_BBOX_HEIGHT / 2 -2 );
		} else
			this->vobject->SetPosition(x-5, y + TURTLE_BBOX_HEIGHT / 2 -2 );
	}

	vobject->Update(dt, coObjects);
	if (this->type == TYPE_TURTLE) {
		if (state == TURTLE_STATE_WALKING) {
			if (!vobject->GetIsOnPlatform()) {
				vx = -vx;
			}
		}
	}
	CGameObject::Update(dt, coObjects);
	isOnPlatform = false;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CTurtle::Render()
{
	int aniId = -1;
	if (state == TURTLE_STATE_DIE)
	{
		if (this->type == TYPE_TURTLE) {
			aniId = ID_ANI_TURTLE_DIE;
		}
		else {
			aniId = ID_ANI_GREEN_TURTLE_DIE;
		}
	}
	else {
		aniId=GetAniId();
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//vobject->Render();
	//RenderBoundingBox();
}

void CTurtle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case TURTLE_STATE_DIE:
		die_start = GetTickCount64();
		y -= (TURTLE_BBOX_HEIGHT - TURTLE_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0.002f;
		break;
	case TURTLE_STATE_WALKING:
		y -= (TURTLE_BBOX_HEIGHT - TURTLE_BBOX_HEIGHT_DIE) / 2;
		vx = -TURTLE_WALKING_SPEED;
		ay = 0.002f;
		break;
	case TURTLE_STATE_SPIN:
		ay = 0.002f;
		break;
	case TURTLE_STATE_SHELL:
		die_start = GetTickCount64();
		ay = 0;
		vx = 0;
		vy = 0;
		break;
	}
}
int CTurtle:: GetAniId() {
	int aniID = -1;
	if (this->type == TYPE_TURTLE) {

		if (this->isOnPlatform) {
			if (vx >= 0)
				aniID = ID_ANI_TURTLE_WALKING_RIGHT;
			else aniID = ID_ANI_TURTLE_WALKING_LEFT;
		}
		if (state == TURTLE_STATE_SPIN) {
			aniID = ID_ANI_TURTLE_SPIN;
		}
		if (state == TURTLE_STATE_HEAL) {
			aniID = ID_ANI_TURTLE_HEAL;
		}
		if (state == TURTLE_STATE_SHELL) {
			aniID = ID_ANI_TURTLE_DIE;
		}
		if (aniID == -1) aniID = ID_ANI_TURTLE_IDLE;
	}
	else if (this->type == TYPE_TURTLE_GREEN) {

		if (this->isOnPlatform) {
			if (vx >= 0)
				aniID = ID_ANI_GREEN_TURTLE_WALKING_RIGHT;
			else aniID = ID_ANI_GREEN_TURTLE_WALKING_LEFT;
		}
		if (state == TURTLE_STATE_SPIN) {
			aniID = ID_ANI_GREEN_TURTLE_SPIN;
		}
		if (state == TURTLE_STATE_HEAL) {
			aniID = ID_ANI_GREEN_TURTLE_HEAL;
		}
		if (state == TURTLE_STATE_SHELL) {
			aniID = ID_ANI_GREEN_TURTLE_DIE;
		}
		if (aniID == -1) aniID = ID_ANI_GREEN_TURTLE_IDLE;
	}
	return aniID;
}

