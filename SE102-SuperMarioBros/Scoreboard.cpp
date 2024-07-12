#include "Scoreboard.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CScoreboard::RenderBoundingBox()
{
	
}

void CScoreboard::Render()
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	float scbx = cx;
	float scby = cy;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_SCOREBOARD)->Render(scbx + 160, scby + 205);
}

void CScoreboard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//float cellWidth_div_2 = this->Width / 2;
	//l = x - cellWidth_div_2;
	//t = y - this->Height / 2;
	//r = l + this->Width;
	//b = t + this->Height;
}
int CScoreboard::IsDirectionColliable(float nx, float ny)
{
	/*if (nx == 0 && ny == -1) return 1;
	else */
	return 0;
}
void CScoreboard::Update(DWORD dt) {
	timeLeft -= dt / 1000;
	if (timeLeft < 0) timeLeft = 0;
}