#include "Gift.h"

void CGift::Render()
{
	int aniID = ID_ANI_GIFT;
	if (isOpened) {
		aniID = ID_ANI_GIFTOPENED;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);

	//RenderBoundingBox();
}

void CGift::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GIFT_BBOX_WIDTH / 2;
	t = y - GIFT_BBOX_HEIGHT / 2;
	r = l + GIFT_BBOX_WIDTH;
	b = t + GIFT_BBOX_HEIGHT;
}