#include "ShutomeCutIn.h"

#define TEX_SHUTOME "shutome_face.png"

ShutomeCutIn::ShutomeCutIn(int area)
    : Task((int)ETaskPrio::EUI)
{
    mpFace = CImage::CreateImage(TEX_SHUTOME);//姑の顔の画像入れる
    if (area == 1)
    {
        mpSerif = CImage::CreateImage("吹き出し1.png");//セリフ入りの吹き出し画像入れる
    }
    else
    {
        mpSerif = CImage::CreateImage("吹き出し2.png");//セリフ入りの吹き出し画像入れる
    }

    mTimer = 120;   // 2秒
    mArea = area;
}

ShutomeCutIn::~ShutomeCutIn()
{
    if (mpFace != nullptr)
    {
        delete mpFace;
        mpFace = nullptr;
        delete mpSerif;
        mpSerif = nullptr;
    }
}

void ShutomeCutIn::Update()
{
    mTimer--;

    if (mTimer <= 0)
    {
        Kill(); // タスク削除
    }
}

void ShutomeCutIn::PreRender()
{
    CVector2D pos;

    pos.x = 50;
    pos.y = SCREEN_HEIGHT - 250;

    mpFace->SetPos(CVector2D(100, SCREEN_HEIGHT - 725));
    mpFace->Draw();

    mpSerif->SetPos(CVector2D(300, SCREEN_HEIGHT - 700));
    mpSerif->Draw();
}