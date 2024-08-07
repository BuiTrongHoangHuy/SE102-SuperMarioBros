#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		mario->canTele = true;
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		mario->canTele = true;
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACCON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_ATTACK);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		mario->canTele = false;
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		mario->canTele = false;
		break;
	case DIK_A:
		if (mario->GetIsHold()) {
			mario->SetIsHold(false);
			mario->SetIsReleaseHold(true);
		}
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A)&& !mario->isAttacking)
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else if (mario->isAttacking) {

		}else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT) )
	{
		if (game->IsKeyDown(DIK_A) && !mario->isAttacking)
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else if (mario->isAttacking) {

		}
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else if (mario->isAttacking)
	{
	//	mario->SetState(MARIO_STATE_ATTACK);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}