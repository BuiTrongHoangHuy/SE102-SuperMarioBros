#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CBackGroundObject : public CGameObject
{
protected:
	float Width;
	float Height;
	int spriteId;

public:
	CBackGroundObject(float x, float y,
		float width, float height,
		int sprite_id) :CGameObject(x, y)
	{
		this->Width = width;
		this->Height = height;
		this->spriteId = sprite_id;
	}

	int IsDirectionColliable(float nx, float ny);
	virtual int IsBlocking() { return 0; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};

typedef CBackGroundObject* LPBACKGROUNDOBJECT;