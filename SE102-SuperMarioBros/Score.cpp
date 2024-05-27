#include "Score.h"

void CScore::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(ID_SPIRTE_SCORE)->Draw(x, y);
	
	//RenderBoundingBox();
}

void CScore::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SCORE_BBOX_WIDTH / 2 + 1;
	t = y - SCORE_BBOX_HEIGHT / 2;
	r = l + SCORE_BBOX_WIDTH - 1;
	b = t + SCORE_BBOX_HEIGHT;
}
void CScore:: OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}
void CScore::OnCollisionWith(LPCOLLISIONEVENT e) {

}
void CScore::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	if (vy >= 0) {
		isDeleted = true;
		this->Delete();
	}
}
CScore::CScore(float x, float y) :CGameObject(x, y) {
	this->vy = -0.1f;
	this->ay = 0.0001f;
}
