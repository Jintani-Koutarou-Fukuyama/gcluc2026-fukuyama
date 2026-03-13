#include "Obstacle.h"
#include "Player.h"

Obstacle::Obstacle(const CVector3D& pos)
    : ObjectBase(pos, 40.0f)
{
    int type = rand() % 2;

    if (type == 0)
    {
        mpImage = CImage::CreateImage("kibori.png");
    }
    else
    {
        mpImage = CImage::CreateImage("tubo.png");
    }

    mpImage->SetSize(200, 200);
    mpImage->SetCenter(CVector2D(95, 170));
}

void Obstacle::Update()
{
    mpImage->SetPos(CalcScreenPos());

    Player* player = Player::GetInstance();
    if (player == nullptr) return;

    if (player->GetPos().y > 0) return; // ƒWƒƒƒ“ƒv’†‚Í–³Ž‹

    float dx = player->GetPos().x - mPos.x;
    float dz = player->GetPos().z - mPos.z;

    float dist = sqrtf(dx * dx + dz * dz);

    float minDist = (mCollisionRange + player->GetCollisionRange())*0.8f;

    if (dist < minDist)
    {
        player->SetPos(player->GetPos() + CVector3D(dx, 0, dz) * 0.05f);
    }
}

void Obstacle::Render()
{
    mpImage->Draw();
}