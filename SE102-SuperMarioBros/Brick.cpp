#include "Brick.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (type == 1) {
		animations->Get(ID_ANI_BRICK_LINE)->Render(x, y);
	}
	else if (type == 2) {
		animations->Get(ID_ANI_BRICK_GLASS)->Render(x, y);

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