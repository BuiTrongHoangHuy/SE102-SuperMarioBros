#include "Score.h"

void CScore::Render()
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(ID_SPIRTE_SCORE)->Draw(x, y);
	RenderBoundingBox();
}

void CScore::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SCORE_BBOX_WIDTH / 2 + 1;
	t = y - SCORE_BBOX_HEIGHT / 2;
	r = l + SCORE_BBOX_WIDTH - 1;
	b = t + SCORE_BBOX_HEIGHT;
}