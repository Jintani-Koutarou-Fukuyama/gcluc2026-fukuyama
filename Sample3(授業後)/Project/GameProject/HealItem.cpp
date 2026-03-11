#include "HealItem.h"
#include "Player.h"


HealItem::HealItem(const CVector3D& pos)
	: ObjectBase(pos, 40.0f)
{
    mpImage = CImage::CreateImage("kaihuku.png");

    //mpImage->SetSize(200, 200);
    mpImage->SetCenter(mpImage->GetSize() * 0.5f);

    mTag = ETag::EHEALITEM;
}

void HealItem::Update()
{
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