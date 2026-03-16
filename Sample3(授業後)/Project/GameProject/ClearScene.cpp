#include"ClearScene.h"
#include"SceneManager.h"


#define CREARIMG "CrearScene.png"//←ここにゲームクリア画像をのせる

//コンストラクタ
ClearScene::ClearScene()
	:mpTitleImg(nullptr)
{
	//ここに:ClearScene()が生成されたときに呼び出したい処理を入れる
	RankTime = false;//フラグをオフにする
	
	// タイトル画像を読み込み
	mpTitleImg = CImage::CreateImage(CREARIMG);
	//数字の読み込み
	mpNumberImg = CImage::CreateImage("number.png");

	printf("ゲームクリアになりました");
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
	
	printf("シーンが変わりました\n");
}


//更新処理
void ClearScene::Update()
{
	//ここに:ClearScene()があるときにずっと更新したい処理を入れる
	
	// [Enter]キーでゲームへ移行
	if (PUSH(CInput::eButton10))
	{
		//シーンをゲームに変更
		SceneManager::ChangeScene(SceneManager::GAME);

	}
	
	if (!RankTime)//フラグがONだったら何もしない
	{
		//クリアタイムの評価によって展開を変える
		if (mClearTime <= 30)//クリアタイムが30秒いないだったらA評価
		{
			printf("A評価\n");
			RankTime = true;
		}
		else if (mClearTime <= 40)//クリアタイムが40秒いないだったらB評価
		{
			printf("B評価\n");
			RankTime = true;
		}
		else//クリアタイムが40秒以上だったらC評価
		{
			printf("C評価\n");
			RankTime = true;
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
	//ここに:ClearScene()があるときにずっと描画したいしたい処理を入れる
	mpTitleImg->Draw();

	int total = mClearTime;
	int min = total / 60;
	int sec = total % 60;

	int tx = 340;
	int ty = 500;

	// 分
	DrawNumber(min / 10, tx, ty);
	DrawNumber(min % 10, tx + 110, ty);

	// コロン（:）
	DrawNumber(10, tx + 220, ty);

	// 秒
	DrawNumber(sec / 10, tx + 330, ty);
	DrawNumber(sec % 10, tx + 440, ty);


}

void ClearScene::Init()
{
	//ゲームオーバー、ゲームクリアのフラグをリセット（リトライ用）
	SceneManager::Instance()->isclear = false;
	SceneManager::Instance()->isover = false;
	SceneManager::Instance()->requestChange = false;
	mClearTime = SceneManager::Instance()->clearTime;

}
