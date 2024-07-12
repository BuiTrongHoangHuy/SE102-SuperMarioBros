#include "Brick.h"
#include "Button.h"
#include "PlayScene.h"
void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (type == 1) {
		animations->Get(ID_ANI_BRICK_LINE)->Render(x, y);
	}
	else if (type == 2) {
		animations->Get(ID_ANI_BRICK_GLASS)->Render(x, y);

	}
	else if (type == 3) {
		animations->Get(ID_ANI_BRICK_HIDDEN)->Render(x, y);
	}
	else if (type == 4) {
		animations->Get(ID_ANI_BRICK_BUTTON)->Render(x, y);
	}
	else {
		animations->Get(ID_ANI_BRICK)->Render(x, y);
	}
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2 + 1;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH - 1;
	b = t + BRICK_BBOX_HEIGHT - 1;
}
void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if (type == 2) {
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);

		if ((state == BRICK_STATE_DIE) && (GetTickCount64() - die_start > BRICK_DIE_TIMEOUT))
		{
			if (isButton) {

				LPGAMEOBJECT button = new CButton(x, y -16);
				LPSCENE s = CGame::GetInstance()->GetCurrentScene();
				LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
				if (this != nullptr) {
					p->PushNewObject(button, button);
				}
				LPGAMEOBJECT brick = new CBrick(x, y,4,0);
				p->PushNewObject(brick, brick);

			}
			isDeleted = true;
			this->Delete();
			return;
		}

	}
}

void CBrick::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		break;
	case BRICK_STATE_WALKING:
		break;
	}
}
