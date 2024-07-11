#pragma once
#include "GameObject.h"
using namespace std;
class CSpawner : public CGameObject
{
protected:
    vector<CGameObject> spawList;
    //vector<LPGAMEOBJECT> spawList2; 
    string filePath;
    float width;
    float height;
public:
    vector<LPGAMEOBJECT> spawList2;

    CSpawner( float l, float t, float r, float b,string filePath)
    {
        x = l;
        y = t;
        width = r - l;
        height = b - t;
        this->filePath = filePath;
        LoadSpawnList();
    }

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render() ;
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
    void RenderBoundingBox(void);
    void LoadSpawnList();
    int IsCollidable() { return 1; }
    int IsBlocking() { return 0; }
    void LoadObject(string line);
    void OnCollisionWith(LPCOLLISIONEVENT e);

};