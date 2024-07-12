#include "Spawner.h"
#include <iostream>
#include <fstream>
#include "AssetIDs.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "PlatformII.h"
#include "BackGroundObject.h"
#include "SampleKeyEventHandler.h"
#include "Gift.h"
#include "Pipe.h"
#include "Turtle.h"
#include "Leaf.h"
#include "Paragoomba.h"
#include "Brick.h"
#include "Goomba.h"
#include "Parakoopa.h"
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CSpawner::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CSpawner::Render()
{
	RenderBoundingBox();
}
void CSpawner::RenderBoundingBox()
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

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CSpawner::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = x + width / 2;
	b = y + height / 2;
}
void CSpawner::LoadSpawnList() {
	DebugOut(L"[INFO] Start loading scene from : %s \n", this->filePath);
	wstring path = ToWSTR(filePath);
	ifstream f;
	f.open(path.c_str());

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		//case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: LoadObject(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", this->filePath);
}

void CSpawner::LoadObject(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_PARAGOOMBA: obj = new CParagoomba(x, y); break;
	case OBJECT_TYPE_PARAKOOPA: obj = new CParakoopa(x, y); break;
	case OBJECT_TYPE_BRICK: {
		int type = atoi(tokens[3].c_str());
		obj = new CBrick(x, y, type); break;
	}
	case OBJECT_TYPE_COIN: {
		int typeCoin = (int)atoi(tokens[3].c_str());
		obj = new CCoin(x, y, typeCoin);
		break;
	}
	case OBJECT_TYPE_GIFT:
	{
		int typeGift = (int)atoi(tokens[3].c_str());
		obj = new CGift(x, y, typeGift);
		break;
	}
	case OBJECT_TYPE_TURTLE:
	{
		if (!tokens[3].empty()) {
			int type = (int)atoi(tokens[3].c_str());
			obj = new CTurtle(x, y, type);
		}
		else {
			obj = new CTurtle(x, y);
		}
		break;
	}
	case OBJECT_TYPE_PIPE: {
		int height = atoi(tokens[3].c_str());
		int type = atoi(tokens[4].c_str());
		obj = new CPipe(x, y, height, type); break; }
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_PLATFORMII: {
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int height = atoi(tokens[6].c_str());
		int sprite_top_left = atoi(tokens[7].c_str());
		int sprite_top_middle = atoi(tokens[8].c_str());
		int sprite_top_right = atoi(tokens[9].c_str());
		int sprite_middle_left = atoi(tokens[10].c_str());
		int sprite_middle = atoi(tokens[11].c_str());
		int sprite_middle_right = atoi(tokens[12].c_str());
		int sprite_bottom_left = atoi(tokens[13].c_str());
		int sprite_bottom_middle = atoi(tokens[14].c_str());
		int sprite_bottom_right = atoi(tokens[15].c_str());
		int type = atoi(tokens[16].c_str());
		obj = new CPlatformII(
			x, y,
			cell_width, cell_height, length, height,
			sprite_top_left, sprite_top_middle, sprite_top_right,
			sprite_middle_left, sprite_middle, sprite_middle_right,
			sprite_bottom_left, sprite_bottom_middle, sprite_bottom_right,
			type
		);
		break;
	}
	case OBJECT_TYPE_BACKGROUNDOBJECT:
	{
		float width = (float)atof(tokens[3].c_str());
		float height = (float)atof(tokens[4].c_str());
		int sprite = atoi(tokens[5].c_str());
		obj = new CBackGroundObject(
			x, y, width, height, sprite
		);
		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	this->spawList2.push_back(obj);
}
void CSpawner::OnCollisionWith(LPCOLLISIONEVENT e) {

	//if (dynamic_cast<CGoomba*>(e->obj))
	//{
	//	DebugOut(L"[INFO] hehe!\n");
	//}
}