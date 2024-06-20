#include "PlatformII.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CPlatformII::RenderBoundingBox()
{
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

	float xx = x - this->cellWidth / 2 + rect.right / 2;
	float yy = y - this->cellHeight / 2 + rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CPlatformII::Render()
{
	if (this->length <= 0 || this->height <=0) return;
	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	//Draw top row
	s->Get(this->spriteIdTopLeft)->Draw(xx, yy);
	xx += this->cellWidth;
	for (int i = 1; i < this->length - 1; i++) {
		s->Get(this->spriteIdTopMiddle)->Draw(xx, yy);
		xx += this->cellWidth;
	}
	if (length > 1) {
		s->Get(this->spriteIdTopRight)->Draw(xx, yy);
	}

	//Draw middle row
	xx = x;
	yy += this->cellHeight;
	
	for (int j = 1 ; j < this->height - 1; j++) {
		s->Get(this->spriteIdMiddleLeft)->Draw(xx, yy);
		xx += this->cellWidth;
		for (int i = 1; i < this->length - 1; i++) {
			s->Get(this->spriteIdMiddle)->Draw(xx, yy);
			xx += this->cellWidth;
		}
		if (length > 1) {
			s->Get(spriteIdMiddleRight)->Draw(xx, yy);
		}
		xx = x;
		yy += this->cellHeight;
	}

	//Draw bottom row
	if (height > 1) {
		s->Get(this->spriteIdBottomLeft)->Draw(xx, yy);
		xx += this->cellWidth;
		for (int i = 1; i < this->length - 1; i++) {
			s->Get(this->spriteIdBottomMiddle)->Draw(xx, yy);
			xx += this->cellWidth;
		}
		if (length > 1) {
			s->Get(this->spriteIdBottomRight)->Draw(xx, yy);
		}
	}
		RenderBoundingBox();
}

void CPlatformII::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	float cellHeight_div_2 = this->cellHeight / 2;
	l = x - cellWidth_div_2;
	t = y - cellHeight_div_2;
	r = l + this->cellWidth * this->length;
	b = t + this->cellHeight *3;
}
int CPlatformII::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}