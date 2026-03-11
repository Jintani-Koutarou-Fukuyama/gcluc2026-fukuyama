#include "Obstacle.h"
#include "Player.h"

Obstacle::Obstacle(const CVector3D& pos)
    : ObjectBase(pos, 40.0f)
{
    int type = rand() % 2;

    if (type == 0)
    {
        mpImage = CImage::CreateImage("kuma.png");
    }
    else
    {
        mpImage = CImage::CreateImage("tubo.png");
    }

    mpImage->SetSize(120, 120);
    mpImage->SetCenter(mpImage->GetSize() * 0.5f);
}

void Obstacle::Update()
{
    mpImage->SetPos(CalcScreenPos());

    Player* player = Player::GetInstance();
    if (player == nullptr) return;

    CVector3D ppos = player->GetPos();

    float dx = ppos.x - mPos.x;
    float dz = ppos.z - mPos.z;

    float dist = sqrtf(dx * dx + dz * dz);

    if (dist < 90.0f)
    {
        player->TakeDamage(1);
    }
}

void Obstacle::Render()
{
    mpImage->Draw();
}