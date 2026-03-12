#include "HealItem.h"
#include "Player.h"


HealItem::HealItem(const CVector3D& pos)
	: ObjectBase(pos, 40.0f)
{
    mpImage = CImage::CreateImage("kaihuku.png");

    mpImage->SetSize(200, 200);
    //mpShadowImg->SetSize(160, 80);
    mpImage->SetCenter(CVector2D(100,150));

    mFloatTime = 0.0f;

    mTag = ETag::EHEALITEM;
}

void HealItem::Update()
{
    //mFloatTime += 0.1f;
    //mPos.y = sinf(mFloatTime) * 10;
    mpImage->SetPos(CalcScreenPos());

    Player* player = Player::GetInstance();
    if (player == nullptr) return;

    CVector3D ppos = player->GetPos();

    float dx = ppos.x - mPos.x;
    float dz = ppos.z - mPos.z;

    float dist = sqrtf(dx * dx + dz * dz);

    if (dist < 80.0f)
    {
        player->Heal(1);
        Kill();
    }
    
}

void HealItem::Render()
{
	mpImage->Draw();
}