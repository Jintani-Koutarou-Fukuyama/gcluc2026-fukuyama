#include"ClearScene.h"
#include"SceneManager.h"


#define CREARIMG "クリア画面1.png"//←ここにゲームクリア画像をのせる

//コンストラクタ
ClearScene::ClearScene()
	:mpTitleImg(nullptr)
	,mClearTime(0)
{
	//ここに:ClearScene()が生成されたときに呼び出したい処理を入れる
	RankTime = false;//フラグをオフにする
	
	// タイトル画像を読み込み
	mpTitleImg = CImage::CreateImage(CREARIMG);
	//数字の読み込み
	mpNumberImg = CImage::CreateImage("number.png");

	//効果音の読み込み
	SOUND("clear_se")->Load("clear.wav", 1, false);
	SOUND("rank_s")->Load("hyoukaS.wav", 1, false);
	SOUND("rank_a")->Load("hyoukaAB.wav", 1, false);
	SOUND("rank_b")->Load("hyoukaAB.wav", 1, false);

	// クリア画面表示音
	SOUND("clear_se")->Play(false);

	mpRankImg = nullptr;

	printf("ゲームクリアになりました\n");
}

//デストラクタ
ClearScene::~ClearScene()
{
	//ここに:ClearScene()が破棄されたときに呼び出したい処理を入れる

	// ゲームクリアの画像を削除
	if (mpTitleImg != nullptr)
	{
		delete mpTitleImg;
		mpTitleImg = nullptr;
	}
	//数字の画像を削除
	if (mpNumberImg != nullptr) {
		delete mpNumberImg;
		mpNumberImg = nullptr;
	}
	if (mpRankImg != nullptr)
	{
		delete mpRankImg;
		mpRankImg = nullptr;
	}
	
	printf("シーンが変わりました\n");
}


//更新処理
void ClearScene::Update()
{
	if (PUSH(CInput::eButton10))
	{
		if (!RankTime)
		{
			// ここで評価判定
			if (mClearTime <= 30)
			{
				mpRankImg = CImage::CreateImage("評価S.png");
				SOUND("rank_s")->Play(false);   // ← Sの音
				printf("S評価\n");
			}
			else if (mClearTime <= 40)
			{
				mpRankImg = CImage::CreateImage("評価A.png");
				SOUND("rank_a")->Play(false);   // ← Aの音
				printf("A評価\n");
			}
			else
			{
				mpRankImg = CImage::CreateImage("評価B.png");
				SOUND("rank_b")->Play(false);   // ← Bの音
				printf("B評価\n");
			}
			

			RankTime = true;
		}
		else
		{
			SceneManager::ChangeScene(SceneManager::GAME);
		}
	}
}

void ClearScene::DrawNumber(int num, int x, int y)
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

//描画処理
void ClearScene::Draw()
{
	//クリアタイム
	if (!RankTime)
	{
		mpTitleImg->Draw();

		int total = mClearTime;
		int min = total / 60;
		int sec = total % 60;

		int tx = 540;
		int ty = 270;

		DrawNumber(min / 10, tx, ty);
		DrawNumber(min % 10, tx + 110, ty);

		DrawNumber(10, tx + 220, ty);

		DrawNumber(sec / 10, tx + 330, ty);
		DrawNumber(sec % 10, tx + 440, ty);

		//ベストタイム
		int best = SceneManager::Instance()->bestTime;

		int bmin = best / 60;
		int bsec = best % 60;

		int bx = 560;
		int by = 430;

		DrawNumber(bmin / 10, bx, by);
		DrawNumber(bmin % 10, bx + 80, by);

		DrawNumber(10, bx + 140, by);

		DrawNumber(bsec / 10, bx + 190, by);
		DrawNumber(bsec % 10, bx + 270, by);
	}
	else
	{
		if (mpRankImg)
		{
			mpRankImg->Draw();
		}
	}

	
}

void ClearScene::Init()
{
	//ゲームオーバー、ゲームクリアのフラグをリセット（リトライ用）
	SceneManager::Instance()->isclear = false;
	SceneManager::Instance()->isover = false;
	SceneManager::Instance()->requestChange = false;
	mClearTime = SceneManager::Instance()->clearTime;
	if (mClearTime < SceneManager::Instance()->bestTime)
	{
		SceneManager::Instance()->bestTime = mClearTime;
	}
}
