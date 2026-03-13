#include "ShutomeCutIn.h"

#define TEX_SHUTOME ""

ShutomeCutIn::ShutomeCutIn(int area)
    : Task((int)ETaskPrio::EUI)
{
    mpFace = CImage::CreateImage(TEX_SHUTOME);//姑の顔の画像入れる
    if (area == 1)
    {
        mpSerif = CImage::CreateImage("");//セリフ入りの吹き出し画像入れる
    }
    else
    {
        mpSerif = CImage::CreateImage("");//セリフ入りの吹き出し画像入れる
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

    pos.x = 100;
    pos.y = 100;

    mpFace->SetPos(pos);
    mpFace->SetSize(300, 300);
    mpFace->Draw();

    mpSerif->SetPos(CVector2D(420, 120));
    mpSerif->SetSize(400, 200);
    mpSerif->Draw();
}