#include "Ui.h"
#include "Player.h"

#define TEX_SHADOW "heart.png"

const int mMmaxHp = 5;

//コンストラクタ
Ui::Ui()
	: Task((int)ETaskPrio::EUI)
	, mpHpImg(nullptr)
{
	// HP画像を読み込み
	mpHpImg = CImage::CreateImage(TEX_SHADOW);
	//数字の画像を読み込み
	mpNumberImg = CImage::CreateImage("number.png");

	mTimer = 0;

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

	if (mpNumberImg != nullptr)
	{
		delete mpNumberImg;
		mpNumberImg = nullptr;
	}
}

void Ui::Update()
{
	mTimer++;
	if (Player::GetInstance() != nullptr)
	{
		mpHp = Player::GetInstance()->GetHp();
	}
}

void Ui::PreRender()
{
	//HPの表示
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
	
	//タイマーの表示
	int total = mTimer / 60;
	int min = total / 60;
	int sec = total % 60;

	int tx = SCREEN_WIDTH - 550;
	int ty = 20;

	DrawNumber(min / 10, tx, ty);
	DrawNumber(min % 10, tx + 110, ty);

	DrawNumber(10, tx + 220, ty);

	DrawNumber(sec / 10, tx + 330, ty);
	DrawNumber(sec % 10, tx + 440, ty);
	
}

void Ui::DrawNumber(int num, int x, int y)
{
	int w = 64;
	int h = 64;

	int sx;
	int sy;

	// 0～4
	if (num <= 4)
	{
		sx = num * w;
		sy = 0;
	}
	// 5～9
	else if (num <= 9)
	{
		sx = (num - 5) * w;
		sy = h;
	}
	// :
	else
	{
		sx = 0;
		sy = h * 2;
	}

	mpNumberImg->SetRect(sx, sy, sx + w, sy + h);
	mpNumberImg->SetSize(120, 120);
	mpNumberImg->SetPos(CVector2D(x, y));
	mpNumberImg->Draw();
}