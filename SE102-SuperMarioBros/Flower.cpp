#include "Flower.h"
#include "Animations.h"
#include "debug.h"
#include "PlayScene.h"
#include "Fireball.h"
CFlower::CFlower(float x, float y) : CGameObject(x, y)
{
    ay = 0.002f;
    this->x = x;
    this->y = y;
    this->startY = y;
    this->endY = y - FLOWER_BBOX_HEIGHT;
    this->isHidden = false;
    SetState(FLOWER_STATE_APPEARING);
    lastShootTime = 0;
}

void CFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - FLOWER_BBOX_WIDTH / 2;
    top = y - FLOWER_BBOX_HEIGHT / 2;
    right = left + FLOWER_BBOX_WIDTH;
    bottom = top + FLOWER_BBOX_HEIGHT;
}
void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    //vy += ay * dt;

    CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
    CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());
    float marioX, marioY;
    mario->GetPosition(marioX, marioY);
    
    if (state == FLOWER_STATE_APPEARING) {
        if (y <= endY ) {
            y = endY;
            SetState(FLOWER_STATE_VISIBLE);
        }

    } else if (state == FLOWER_STATE_DISAPPEARING) {
        if (y >= startY && isHidden) {
            y = startY;
            SetState(FLOWER_STATE_HIDDEN);
        } else if (y >= startY) {
            y = startY;
            SetState(FLOWER_STATE_APPEARING);
        }
    } else if (state == FLOWER_STATE_VISIBLE) {
        if ((marioX < x - 100) || (marioX > x + 100)){
            SetState(FLOWER_STATE_DISAPPEARING);
            isHidden = false;
            DebugOut(L"[INFO] disappear!\n");

        }
        else if ((marioX > x - 40) && (marioX < x + 40)) {
            SetState(FLOWER_STATE_DISAPPEARING);
            isHidden = true;
            // ban
        }
        else {
            if (state == FLOWER_STATE_VISIBLE && GetTickCount64() - lastShootTime > FLOWER_SHOOT_INTERVAL) 
            {
                Shoot(marioX, marioY); 
                lastShootTime = GetTickCount64(); 
            }
        }
    }
    else if (state == FLOWER_STATE_HIDDEN) {
        if ((marioX < x - 40) || (marioX > x + 40)) {
            SetState(FLOWER_STATE_APPEARING);
        }
    }
    /*else if ((marioX > x - 50) || (marioX < x + 50)) {
        SetState(FLOWER_STATE_DISAPPEARING);
        if (y >= startY) {
            y = startY;
            SetState(FLOWER_STATE_HIDDEN);
        }
    }*/
    CGameObject::Update(dt);
    CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CFlower::Render()
{
    if (state != FLOWER_STATE_HIDDEN) {
        int aniID = GetAniID();
        CAnimations::GetInstance()->Get(aniID)->Render(x, y);
    }
}
void CFlower::OnNoCollision(DWORD dt) {
  //  x += vx * dt;
    y += vy * dt;
}
void CFlower::OnCollisionWith(LPCOLLISIONEVENT e) {
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CFlower*>(e->obj)) return;

    if (e->ny != 0)
    {
        vy = 0;
    }
    else if (e->nx != 0)
    {
    }
}
void CFlower::SetState(int state) {
    CGameObject::SetState(state);

    switch (state)
    {
    case FLOWER_STATE_APPEARING:
        vy = -FLOWER_APPEAR_SPEED;
        break;
    case FLOWER_STATE_DISAPPEARING:
        vy = FLOWER_APPEAR_SPEED;
        break;
    case FLOWER_STATE_VISIBLE:
        vy = 0;
        break;
    case FLOWER_STATE_HIDDEN:
        vy = 0;
        break;
    default:
        break;
    }

}
int CFlower::GetAniID() {
    CPlayScene* scene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
    CMario* mario = dynamic_cast<CMario*>(scene->GetPlayer());
    float marioX, marioY;
    mario->GetPosition(marioX, marioY);
    int aniID = -1;
    if (marioX <= x && marioY>=y) {
        aniID = ID_ANI_FLOWER_APPEAR_LEFT_BOT;
    }
    else if(marioX <=x && marioY < y) {
        aniID = ID_ANI_FLOWER_APPEAR_LEFT_TOP;
    }
    else if (marioX > x && marioY >= y) {
        aniID = ID_ANI_FLOWER_APPEAR_RIGHT_BOT;
    }
    else if (marioX > x && marioY < y) {
        aniID = ID_ANI_FLOWER_APPEAR_RIGHT_TOP;
    }
    return aniID;
}
void CFlower::Shoot(float marioX, float marioY)
{
    CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

    // Calculate the direction towards Mario
    int directionX = (marioX < this->x) ? -1 : 1;
    int directionY = (marioY < this->y) ? -1 : 1;
    if (marioY<y + 10 && marioY>y - 10) {
        directionY = 0;
    }
    // Create the fireball
   // CFireball* fireball = new CFireball(x, y, direction);
    LPGAMEOBJECT fireball = new CFireball(x, y, directionX,directionY);
    LPSCENE s = CGame::GetInstance()->GetCurrentScene(); 
    LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s); 
    if (this != nullptr) {
        p->AddFowardNewObject(fireball, this);
    }
}