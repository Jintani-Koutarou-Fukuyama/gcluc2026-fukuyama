#include"TutorialScene.h"
#include"SceneManager.h"

#define TITLEIMG "仮タイトル.png"//←ここにチュートリアル画像をのせる
#define TITLE_BGM1 "TITLEBGM1.wav"//チュートリアル画面のBGM１～４好きなの選んでください
#define TITLE_BGM2 "TITLEBGM2.wav"//MP3からwavに変換しないといけない
#define TITLE_BGM3 "TITLEBGM3.wav"
#define TITLE_BGM4 "TITLEBGM4.wav"
#define TUTORIAL1 "チュートリアル1.png"
#define TUTORIAL2 "チュートリアル2.png"
#define TUTORIAL3 "チュートリアル3.png"
#define TUTORIAL4 "チュートリアル4.png"
#define TUTORIAL5 "チュートリアル5.png"

// コンストラクタ
TutorialScene::TutorialScene()
	//:mpTutorialImg(nullptr)
{
	//ここにTutorialScene()が生成されたときに呼び出したい処理を入れる
	mPage = 0;

	mpTutorialImg[0] = CImage::CreateImage(TUTORIAL1);
	mpTutorialImg[1] = CImage::CreateImage(TUTORIAL2);
	mpTutorialImg[2] = CImage::CreateImage(TUTORIAL3);
	mpTutorialImg[3] = CImage::CreateImage(TUTORIAL4);
	mpTutorialImg[4] = CImage::CreateImage(TUTORIAL5);
	// チュートリアル画像を読み込み
	//mpTutorialImg = CImage::CreateImage(TITLEIMG);
	// BGM読み込み
	SOUND("title_bgm")->Load(TITLE_BGM1, 1, false);
	// 再生（trueはループ）
	SOUND("title_bgm")->Play(true);

	printf("チュートリアルになりました\n");

	// 矢印アイコン読み込み
	mpNextIcon = CImage::CreateImage("Enter矢印.png");
	mpNextIcon->SetSize(128, 64);
	mpNextIcon->SetPos(1100, 650);

	// 点滅初期値
	mBlinkAlpha = 1.0f;
	mBlinkSpeed = 0.02f;
	mBlinkUp = false;
}

//デストラクタ
TutorialScene::~TutorialScene()
{
	//ここにTutorialScene()が破棄されたときに呼び出したい処理を入れる
	for (int i = 0; i < 5; i++)
	{
		if (mpTutorialImg[i] != nullptr)
		{
			mpTutorialImg[i]->Release();
			//delete mpTutorialImg[i];
			mpTutorialImg[i] = nullptr;
		}
	}
	// BGM停止
	SOUND("title_bgm")->Stop();

	// タイトルの画像を削除
	/*if (mpTutorialImg != nullptr)
	{
		delete mpTutorialImg;
		mpTutorialImg = nullptr;
	}*/
	printf("シーンが変わりました\n");
	if (mpNextIcon)
	{
		mpNextIcon->Release();
		//delete mpNextIcon;
		mpNextIcon = nullptr;
	}
}

//更新処理
void TutorialScene::Update()
{
	//ここにTutorialScene()があるときにずっと更新したい処理を入れる
	// [Enter]キーでゲームへ移行
	//if (PUSH(CInput::eButton10))
	//{
	//	//シーンをゲームに変更
	//	SceneManager::ChangeScene(SceneManager::GAME);

	//}
	if (PUSH(CInput::eButton10))
	{
		mPage++;  //次のページへ

		if (mPage >= 5)
		{
			SceneManager::ChangeScene(SceneManager::GAME);
			return;
		}
	}

	// 点滅処理
	if (mBlinkUp)
	{
		mBlinkAlpha += mBlinkSpeed;
		if (mBlinkAlpha >= 1.0f)
		{
			mBlinkAlpha = 1.0f;
			mBlinkUp = false;
		}
	}
	else
	{
		mBlinkAlpha -= mBlinkSpeed;
		if (mBlinkAlpha <= 0.0f)
		{
			mBlinkAlpha = 0.0f;
			mBlinkUp = true;
		}
	}

	// α値をセット
	if (mpNextIcon)
	{
		mpNextIcon->SetColor(1.0f, 1.0f, 1.0f, mBlinkAlpha);
	}
}


//描画処理
void TutorialScene::Draw()
{
	//ここにTutorialScene()があるときにずっと描画したいしたい処理を入れる
	//mpTutorialImg->Draw();
	if (mPage < 5)
	{
		mpTutorialImg[mPage]->Draw();
	}
	// 矢印描画
	if (mpNextIcon)
	{
		mpNextIcon->Draw();
	}
}
void TutorialScene::Init()
{

}
