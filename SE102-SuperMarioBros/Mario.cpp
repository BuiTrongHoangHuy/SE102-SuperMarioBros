#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"

#include "Collision.h"
#include "Gift.h"
#include "Mushroom.h"
#include "Turtle.h"
#include "Fireball.h"
#include "Pipe.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	
	isOnPlatform = false;
	if (isHold&& holdTurtle!=nullptr) {
		float mx, my;
		this->GetPosition(mx, my);
		if (vx == 0)
		{
			if (nx > 0) {
				this->holdTurtle->SetPosition(mx + 12, my + 3);
			}

			else {
				this->holdTurtle->SetPosition(mx - 12, my + 3);
			}
		}
		else if (vx > 0) {
			this->holdTurtle->SetPosition(mx + 12, my + 3);

		}
		else {
			this->holdTurtle->SetPosition(mx - 12, my + 3);

		}
		//if (vx<0)
		//	this->holdTurtle->SetPosition(mx - 12, my+3);
		//else {
		//	this->holdTurtle->SetPosition(mx + 12, my+3 );
		//}
		
	}
	if (isReleaseHold) {
		holdTurtle->SetState(TURTLE_STATE_SPIN);
		isKick = true;
		time_kick = GetTickCount64();
		if (vx == 0)
		{
			if (nx > 0) {
				holdTurtle->SetSpeed(0.2f, 0);
			}
			else {
				holdTurtle->SetSpeed(-0.2f, 0);
			}
		}
		else if (vx > 0) {
			holdTurtle->SetSpeed(0.2f, 0);
		}
		else {
			holdTurtle->SetSpeed(-0.2f, 0);
		}
		holdTurtle = nullptr;
		isReleaseHold = false;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CGift*>(e->obj))
		OnCollisionWithGift(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CTurtle*>(e->obj))
		OnCollisionWithTurtle(e);
	else if (dynamic_cast<CFireball*>(e->obj))
		OnCollisionWithFireball(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}
void CMario::OnCollisionWithFireball(LPCOLLISIONEVENT e) {
	CFireball* fireball = dynamic_cast<CFireball*>(e->obj);
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
	e->obj->Delete();
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}
void CMario::OnCollisionWithGift(LPCOLLISIONEVENT e) {
		CGift* gift = dynamic_cast<CGift*>(e->obj);
	if (e->ny > 0) {
		if (gift->GetState() == GIFT_STATE_CLOSED ) {
			gift->SetState(GIFT_STATE_PREOPENED);
			if (gift->GetType() == 0) {
				coin++;
			}
		}
	}
}
void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	if (mushroom->GetState() == MUSHROOM_STATE_WALKING) {
		mushroom->SetState(MUSHROOM_STATE_EATEN);
	}
	if (level == MARIO_LEVEL_SMALL) {
		SetLevel(MARIO_LEVEL_BIG);
	}
	e->obj->Delete();
	
}
void CMario::OnCollisionWithTurtle(LPCOLLISIONEVENT e) {
	CTurtle* turtle = dynamic_cast<CTurtle*>(e->obj);

	// jump on top >> kill Turtle and deflect a bit 
	if (e->ny < 0)
	{
		if (turtle->GetState() != TURTLE_STATE_DIE)
		{
			turtle->SetState(TURTLE_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Turtle
	{
		
		if (untouchable == 0)
		{
			if (turtle->GetState() != TURTLE_STATE_DIE && turtle->GetState()!= TURTLE_STATE_SHELL)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
		if (e->obj->GetState() == TURTLE_STATE_DIE) {
			if (e->nx > 0) {
				if (state == MARIO_STATE_RUNNING_LEFT) {
					isHold = true;
					holdTurtle = turtle;
					turtle->SetState(TURTLE_STATE_SHELL);
				}
				else {
				e->obj->SetState(TURTLE_STATE_SPIN);
				isKick = true;
				time_kick = GetTickCount64();
				e->obj->SetSpeed(-0.2F, 0);
				}

			}
			if (e->nx < 0) {
				if (state == MARIO_STATE_RUNNING_RIGHT) {
					isHold = true;
					holdTurtle = turtle;
					turtle->SetState(TURTLE_STATE_SHELL);
				}
				else {
				isKick = true;
				time_kick = GetTickCount64();
				e->obj->SetState(TURTLE_STATE_SPIN);
				e->obj->SetSpeed(0.2f, 0);
				}
			}
		}
	}
}
void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				if (isKick) {
					aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
					if (GetTickCount64() - time_kick > 200) {
						isKick = false;
						time_kick = 0;
					}
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				if (isKick) {
					aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
					if (GetTickCount64() - time_kick > 200) {
						isKick = false;
						time_kick = 0;
					}
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0) {
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				if (isHold) {
					aniId = ID_ANI_MARIO_HOLD_SHELL_RUNNING_RIGHT;
				}
			}
			else {
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
				if (isHold) {
					aniId = ID_ANI_MARIO_HOLD_SHELL_RUNNING_LEFT;
				}
			}
		}
		else
		{
			if (nx >= 0) {
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				if (isHold) {
					aniId = ID_ANI_MARIO_HOLD_SHELL_RIGHT;
				}
			}
			else{
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
				if (isHold) {
					aniId = ID_ANI_MARIO_HOLD_SHELL_LEFT;
				}
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
		{

			if (vx == 0)
			{
				if (nx > 0) {
					aniId = ID_ANI_MARIO_IDLE_RIGHT;			
					if (isKick) {
						aniId = ID_ANI_MARIO_KICK_RIGHT;
						if (GetTickCount64() - time_kick > 200) {
							isKick = false;
							time_kick = 0;
						}
					}
					if (isHold) {
						aniId = ID_ANI_MARIO_HOLD_SHELL_RIGHT;
					}
				}

				else {
					aniId = ID_ANI_MARIO_IDLE_LEFT;
					if (isKick) {
						aniId = ID_ANI_MARIO_KICK_LEFT;
						if (GetTickCount64() - time_kick > 200) {
							isKick = false;
							time_kick = 0;
						}
					}
					if (isHold) {
						aniId = ID_ANI_MARIO_HOLD_SHELL_LEFT;
					}
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X) {
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				}
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
				if (isHold) {
					aniId = ID_ANI_MARIO_HOLD_SHELL_RUNNING_RIGHT;
				}
				if (isKick) {
					aniId = ID_ANI_MARIO_KICK_RIGHT;
					if (GetTickCount64() - time_kick > 200) {
						isKick = false;
						time_kick = 0;
					}
				}
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X) {
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				
				}
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
				if (isHold) {
					aniId = ID_ANI_MARIO_HOLD_SHELL_RUNNING_LEFT;
				}
				if (isKick) {
					aniId = ID_ANI_MARIO_KICK_LEFT;
					if (GetTickCount64() - time_kick > 200) {
						isKick = false;
						time_kick = 0;
					}
				}
			}
			
		}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			//isOnPlatform = false;

			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

