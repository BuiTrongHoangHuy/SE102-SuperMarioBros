#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CPlatformII : public CGameObject
{
protected:
	int length;				// Unit: cell 
	int height;
	float cellWidth;
	float cellHeight;
	int spriteIdTopLeft, spriteIdTopMiddle, spriteIdTopRight, spriteIdMiddleLeft, spriteIdMiddle, spriteIdMiddleRight, spriteIdBottomLeft, spriteIdBottomMiddle, spriteIdBottomRight;

public:
	CPlatformII(float x, float y,
		float cell_width, float cell_height, int length,int height,
		int sprite_id_top_left, int sprite_id_top_middle, int sprite_id_top_right,int sprite_id_middle_left,
		int sprite_id_middle,int sprire_id_middle_right,int sprite_id_bottom_left,int sprite_id_bottom_middle,int sprite_id_bottom_right) :CGameObject(x, y)
	{
		this->length = length;
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdTopLeft = sprite_id_top_left;
		this->spriteIdTopMiddle = sprite_id_top_middle;
		this->spriteIdTopRight = sprite_id_top_right;
		this->spriteIdMiddleLeft = sprite_id_middle_left;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdMiddleRight = sprire_id_middle_right;
		this->spriteIdBottomLeft = sprite_id_bottom_left;
		this->spriteIdBottomMiddle = sprite_id_bottom_middle;
		this->spriteIdBottomRight = sprite_id_bottom_right;
	}

	int IsDirectionColliable(float nx, float ny);

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};

typedef CPlatformII* LPPLATFORMII;