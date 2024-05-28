#include "Turtle.h"
#include "VirtualObject.h"
#include "PlayScene.h"
CTurtle::CTurtle(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = TURTLE_GRAVITY;
	isOnPlatform = false;
	die_start = -1;
	vobject = new CVirtualObject(x, y + TURTLE_BBOX_HEIGHT / 2 );
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
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CTurtle*>(e->obj)) return;

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
	
	if ((state == TURTLE_STATE_DIE) && (GetTickCount64() - die_start > TURTLE_DIE_TIMEOUT))
	{
		//isDeleted = true;
		return;
	}
	if (vx > 0) {
	this->vobject->SetPosition( x+8, y + TURTLE_BBOX_HEIGHT / 2 -2 );
	}else
		this->vobject->SetPosition(x-8, y + TURTLE_BBOX_HEIGHT / 2 -2 );

	//vector<LPGAMEOBJECT> coObjectsForGhost;
	//for (size_t i = 0; i < coObjects->size(); i++)
	//{
	//	coObjectsForGhost.push_back(coObjects->at(i));
	//}
	//CCollision::GetInstance()->Process(vobject, dt, &coObjectsForGhost);
	vobject->Update(dt, coObjects);
	if (!vobject->GetIsOnPlatform()) {
		vx = -vx;
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
		aniId = ID_ANI_TURTLE_DIE;
	}
	else {
		aniId=GetAniId();
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	vobject->Render();
	//RenderBoundingBox();
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
	int aniID = -1;
	if (this->isOnPlatform) {
		if (vx >= 0)
			aniID = ID_ANI_TURTLE_WALKING_RIGHT;
		else aniID = ID_ANI_TURTLE_WALKING_LEFT;
	}
	if (aniID == -1) aniID = ID_ANI_TURTLE_IDLE;
	return aniID;
}

