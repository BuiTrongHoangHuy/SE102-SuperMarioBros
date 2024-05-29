#include "Pipe.h"
#include "Flower.h"
#include "PlayScene.h"
void CPipe::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_PIPE)->Render(x, y);
	RenderBoundingBox();
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIPE_BBOX_WIDTH / 2 + 1 ;
	t = y - PIPE_BBOX_HEIGHT / 2;
	r = l + PIPE_BBOX_WIDTH - 1 ;
	b = t + PIPE_BBOX_HEIGHT;
}

void CPipe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (check) {
		LPGAMEOBJECT flower = new CFlower(x, y-8);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		if (this != nullptr) {
			p->AddFowardNewObject(flower, this);
		}
		check = false;
	}
}
