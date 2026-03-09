#include "Ui.h"
#include "Player.h"

#define TEX_SHADOW "heart.png"

const int mMmaxHp = 5;

//コンストラクタ
Ui::Ui()
	: Task((int)ETaskPrio::EUI)
	, mpHpImg(nullptr)
{
	// フィールド画像を読み込み
	mpHpImg = CImage::CreateImage(TEX_SHADOW);
}

//デストラクタ
Ui::~Ui()
{
	// HPの画像を削除
	if (mpHpImg != nullptr)
	{
		delete mpHpImg;
		mpHpImg = nullptr;
	}
}

void Ui::Update()
{
	if (Player::GetInstance() != nullptr)
	{
		mpHp = Player::GetInstance()->GetHp();
	}
}

void Ui::PreRender()
{
	int x = 20;
	int y = 20;

	for (int i = 0; i < 5; i++)
	{
		if (i < mpHp)
		{
			mpHpImg->SetPos(CVector2D(x + i * 90, y));
			mpHpImg->Draw();
		}
	}
}
