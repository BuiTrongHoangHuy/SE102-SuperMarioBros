#include "BackGroundObject.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CBackGroundObject::RenderBoundingBox()
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

	float xx = x - this->Width / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CBackGroundObject::Render()
{
	CSprites* s = CSprites::GetInstance();

	s->Get(this->spriteId)->Draw(x, y);
	//RenderBoundingBox();
}

void CBackGroundObject::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->Width / 2;
	l = x - cellWidth_div_2;
	t = y - this->Height / 2;
	r = l + this->Width;
	b = t + this->Height;
}
