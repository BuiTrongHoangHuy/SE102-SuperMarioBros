#include "Pipe.h"
#include "Flower.h"
#include "PlayScene.h"
void CPipe::Render()
{
	/*CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_PIPE)->Render(x, y);*/
	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	//Draw top row
	s->Get(ID_SPRITE_TOP_LEFT)->Draw(xx, yy);
	xx += 16;
	s->Get(ID_SPRITE_TOP_RIGHT)->Draw(xx, yy);

	//Draw middle row
	xx = x;
	yy += 16;
	for (int j = 1; j < this->height - 1; j++) {
		s->Get(ID_SPRITE_BOT_LEFT)->Draw(xx, yy);
		xx += 16;
		s->Get(ID_SPRITE_BOT_RIGHT)->Draw(xx, yy);
		xx = x;
		yy += 16;
	}

	//Draw bottom row
	if (height > 1) {
		s->Get(ID_SPRITE_BOT_LEFT)->Draw(xx, yy);
		xx += 16;
		s->Get(ID_SPRITE_BOT_RIGHT)->Draw(xx, yy);
	}
	//RenderBoundingBox();

}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	/*l = x - PIPE_BBOX_WIDTH / 2 + 1 ;
	t = y - PIPE_BBOX_HEIGHT / 2;
	r = l + PIPE_BBOX_WIDTH - 1 ;
	b = t + PIPE_BBOX_HEIGHT;*/

	float cellWidth_div_2 = 16 / 2;
	float cellHeight_div_2 = 16 / 2;
	l = x - cellWidth_div_2;
	t = y - cellHeight_div_2;
	r = l + 16 * 2;
	b = t + 16 * this->height;
}

void CPipe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (check) {
		LPGAMEOBJECT flower = new CFlower(x+8, y+8);
		LPSCENE s = CGame::GetInstance()->GetCurrentScene();
		LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
		if (this != nullptr) {
			p->AddFowardNewObject(flower, this);
		}
		check = false;
	}
}

void CPipe::RenderBoundingBox() {
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - 16 / 2 + rect.right / 2;
	float yy = y - 16 / 2 + rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}