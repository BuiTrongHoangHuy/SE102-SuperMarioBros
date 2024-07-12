#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Turtle.h"
#include "Parakoopa.h"
#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f
#define MARIO_FLYING_SPEED	0.5f
#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define MARIO_STATE_SIT_KICK		700

#define MARIO_STATE_READY_FLYING	800
#define MARIO_STATE_FLYING	900
#define MARIO_STATE_FALLING		1000

#define MARIO_STATE_ATTACK 1100
#define MARIO_ATTACK_DURATION 1000

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_KICK_RIGHT 2000
#define ID_ANI_MARIO_KICK_LEFT 2001
#define ID_ANI_MARIO_HOLD_SHELL_RIGHT 2100
#define ID_ANI_MARIO_HOLD_SHELL_LEFT 2101
#define ID_ANI_MARIO_HOLD_SHELL_RUNNING_RIGHT 2200
#define ID_ANI_MARIO_HOLD_SHELL_RUNNING_LEFT 2201

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 2500
#define ID_ANI_MARIO_SMALL_KICK_LEFT 2501
#define ID_ANI_MARIO_SMALL_HOLD_SHELL_RIGHT 2600
#define ID_ANI_MARIO_SMALL_HOLD_SHELL_LEFT 2601
#define ID_ANI_MARIO_SMALL_HOLD_SHELL_RUNNING_RIGHT 2700
#define ID_ANI_MARIO_SMALL_HOLD_SHELL_RUNNING_LEFT 2701


// RACCON MARIO
#define ID_ANI_MARIO_RACCON_IDLE_RIGHT 3100
#define ID_ANI_MARIO_RACCON_IDLE_LEFT 3102
					 
#define ID_ANI_MARIO_RACCON_WALKING_RIGHT 3200
#define ID_ANI_MARIO_RACCON_WALKING_LEFT 3201
					 
#define ID_ANI_MARIO_RACCON_RUNNING_RIGHT 3300
#define ID_ANI_MARIO_RACCON_RUNNING_LEFT 3301

#define ID_ANI_MARIO_RACCON_BRACE_RIGHT 3400
#define ID_ANI_MARIO_RACCON_BRACE_LEFT 3401

#define ID_ANI_MARIO_RACCON_JUMP_WALK_RIGHT 3500
#define ID_ANI_MARIO_RACCON_JUMP_WALK_LEFT 3501

#define ID_ANI_MARIO_RACCON_JUMP_RUN_RIGHT 3600
#define ID_ANI_MARIO_RACCON_JUMP_RUN_LEFT 3601

#define ID_ANI_MARIO_RACCON_SIT_RIGHT 3700
#define ID_ANI_MARIO_RACCON_SIT_LEFT 3701

#define ID_ANI_MARIO_RACCON_KICK_RIGHT 3800
#define ID_ANI_MARIO_RACCON_KICK_LEFT 3801
#define ID_ANI_MARIO_RACCON_HOLD_SHELL_RIGHT 3900
#define ID_ANI_MARIO_RACCON_HOLD_SHELL_LEFT 3901
#define ID_ANI_MARIO_RACCON_HOLD_SHELL_RUNNING_RIGHT 4000
#define ID_ANI_MARIO_RACCON_HOLD_SHELL_RUNNING_LEFT 4001

#define ID_ANI_MARIO_RACCON_READY_FLY_RIGHT	4100
#define ID_ANI_MARIO_RACCON_READY_FLY_LEFT	4101
#define ID_ANI_MARIO_RACCON_FLYING_RIGHT 4200
#define ID_ANI_MARIO_RACCON_FLYING_LEFT 4201

#define ID_ANI_MARIO_RACCON_ATTACK_LEFT 4202
#define ID_ANI_MARIO_RACCON_ATTACK_RIGHT 4203

#define ID_ANI_MARIO_UNTOUCHABLE_RIGHT 4300
#define ID_ANI_MARIO_UNTOUCHABLE_LEFT 4301
#define ID_ANI_MARIO_SMALL_UNTOUCHABLE_RIGHT 4400
#define ID_ANI_MARIO_SMALL_UNTOUCHABLE_LEFT 4401
#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCON		3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12

#define MARIO_RACCON_BBOX_WIDTH  14
#define MARIO_RACCON_BBOX_HEIGHT 24
#define MARIO_RACCON_SITTING_BBOX_WIDTH  14
#define MARIO_RACCON_SITTING_BBOX_HEIGHT 16

#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_FLY_TIME 3000
#define MARIO_READY_FLY_TIME 300


class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	BOOLEAN isKick = false;
	BOOLEAN isHold = false;
	BOOLEAN isReleaseHold = false;
	CTurtle* holdTurtle = nullptr;
	CParakoopa* holdParakoopa = nullptr;
	ULONGLONG time_kick;
	ULONGLONG flyStart;
	BOOLEAN isFlying;
	ULONGLONG runningStart;
	BOOLEAN canFly = false;
	BOOLEAN aniFly = false;
	ULONGLONG timeFly=0;
	int coin; 

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithGift(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithTurtle(LPCOLLISIONEVENT e);
	void OnCollisionWithFireball(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithParagoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithFlower(LPCOLLISIONEVENT e);
	void OnCollisionWithSpawner(LPCOLLISIONEVENT e);
	void OnCollisionWithParakoopa(LPCOLLISIONEVENT e);
	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccon();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		time_kick = -1;
		isOnPlatform = false;
		coin = 0;
		flyStart = 0;
		isFlying = false;
		runningStart = 0;
		attackStart = 0;
		isAttacking = false;
	}
	BOOLEAN isAttacking;
	ULONGLONG attackStart;
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void AddCoin() { coin++; }
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void SetIsHold(bool state) { this->isHold = state; }
	void SetIsKick(bool state) { this->isKick = state; }
	void SetIsReleaseHold(bool state) { this->isReleaseHold = state; }
	bool GetIsReleaseHold() { return this->isReleaseHold ; }
	bool GetIsKick() { return this->isKick ; }
	bool GetIsHold() { return this->isHold; }
	bool GetIsOnplatform() { return this->isOnPlatform; }
	int GetLevel() { return this->level; }
	CTurtle* GetHoldTurtle() { return holdTurtle; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};