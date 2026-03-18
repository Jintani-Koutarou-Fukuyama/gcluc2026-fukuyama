#include "Ui.h"
#include "Player.h"
#include"SceneManager.h"

#define TEX_SHADOW "ハート.png"

const int mMmaxHp = 5;

//コンストラクタ
Ui::Ui()
	: Task((int)ETaskPrio::EUI)
	, mpHpImg(nullptr)
	, mpHp(0)
{
	// HP画像を読み込み
	mpHpImg = CImage::CreateImage(TEX_SHADOW);
	//数字の画像を読み込み
	mpNumberImg = CImage::CreateImage("number.png");
	//HPフレームの画像を読み込み
	mpUiFrame = CImage::CreateImage("Frame.png");
	//タイマーフレームの画像を読み込み
	mpUiFrameTimer = CImage::CreateImage("Frame.png");

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

	if (mpUiFrame != nullptr)
	{
		delete mpUiFrame;
		mpUiFrame = nullptr;
	}

	if (mpUiFrameTimer != nullptr)
	{
		delete mpUiFrameTimer;
		mpUiFrameTimer = nullptr;
	}
}

void Ui::Update()
{
	if (Player::GetInstance() != nullptr)
	{
		mpHp = Player::GetInstance()->GetHp();
		// HPが0より大きいときだけタイマーを進める
		if (mpHp > 0)
		{
			mTimer++;
			SceneManager::Instance()->clearTime = mTimer / 60;

		}
	}
}

void Ui::Render()
{//HPフレーム
	mpUiFrame->SetPos(CVector2D(10, 10));
	mpUiFrame->SetSize(350, 150);
	mpUiFrame->Draw();

	//タイマーフレーム
	mpUiFrameTimer->SetPos(CVector2D(SCREEN_WIDTH - 360, 10));
	mpUiFrameTimer->SetSize(350, 150);
	mpUiFrameTimer->Draw();

	//HPの表示
	int x = 20;
	int y = 50;

	for (int i = 0; i < 5; i++)
	{
		if (i < mpHp)
		{
			mpHpImg->SetPos(CVector2D(x + i * 65, y));
			mpHpImg->SetSize(70, 70);
			mpHpImg->Draw();
		}
	}

	//タイマーの表示
	int total = mTimer / 60;
	int min = total / 60;
	int sec = total % 60;

	int tx = SCREEN_WIDTH - 370;
	int ty = 40;


	DrawNumber(min / 10, tx, ty);
	DrawNumber(min % 10, tx + 80, ty);

	DrawNumber(10, tx + 140, ty);

	DrawNumber(sec / 10, tx + 190, ty);
	DrawNumber(sec % 10, tx + 270, ty);

}
void Ui::PreRender()
{
	
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
	mpNumberImg->SetSize(100, 100);
	mpNumberImg->SetPos(CVector2D(x, y));
	mpNumberImg->Draw();
}
int Ui::GetTimeSec() const
{
	return mTimer / 60;  //秒計算
}
