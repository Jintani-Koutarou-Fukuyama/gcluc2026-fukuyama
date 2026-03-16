#include"TutorialScene.h"
#include"SceneManager.h"

#define TITLEIMG "仮タイトル.png"//←ここにチュートリアル画像をのせる
#define TITLE_BGM1 "TITLEBGM1.wav"//チュートリアル画面のBGM１～４好きなの選んでください
#define TITLE_BGM2 "TITLEBGM2.wav"//MP3からwavに変換しないといけない
#define TITLE_BGM3 "TITLEBGM3.wav"
#define TITLE_BGM4 "TITLEBGM4.wav"


// コンストラクタ
TutorialScene::TutorialScene()
	:mpTutorialImg(nullptr)
{
	//ここにTutorialScene()が生成されたときに呼び出したい処理を入れる

	// チュートリアル画像を読み込み
	mpTutorialImg = CImage::CreateImage(TITLEIMG);
	// BGM読み込み
	SOUND("title_bgm")->Load(TITLE_BGM3, 1, false);
	// 再生（trueはループ）
	SOUND("title_bgm")->Play(true);

	printf("チュートリアルになりました\n");

}

//デストラクタ
TutorialScene::~TutorialScene()
{
	//ここにTitleScene()が破棄されたときに呼び出したい処理を入れる

	// BGM停止
	SOUND("title_bgm")->Stop();

	// タイトルの画像を削除
	if (mpTutorialImg != nullptr)
	{
		delete mpTutorialImg;
		mpTutorialImg = nullptr;
	}
	printf("シーンが変わりました\n");
}

//更新処理
void TutorialScene::Update()
{
	//ここにTitleScene()があるときにずっと更新したい処理を入れる
	// [Enter]キーでゲームへ移行
	if (PUSH(CInput::eButton10))
	{
		//シーンをゲームに変更
		SceneManager::ChangeScene(SceneManager::GAME);

	}
}


//描画処理
void TutorialScene::Draw()
{
	//ここにTitleScene()があるときにずっと描画したいしたい処理を入れる
	mpTutorialImg->Draw();

}
void TutorialScene::Init()
{

}
