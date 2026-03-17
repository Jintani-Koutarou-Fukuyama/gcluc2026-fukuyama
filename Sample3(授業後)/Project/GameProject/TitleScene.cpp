#include"TitleScene.h"
#include"SceneManager.h"

#define TITLEIMG "仮タイトル.png"//←ここにタイトル画像をのせる



// コンストラクタ
TitleScene::TitleScene()
	:mpTitleImg(nullptr)
{
	//ここにTitleScene()が生成されたときに呼び出したい処理を入れる

	// タイトル画像を読み込み
	mpTitleImg = CImage::CreateImage(TITLEIMG);
	
	// 再生（trueはループ）
	SOUND("title_bgm")->Play(true);
	
	printf("タイトルになりました\n");
	
}

//デストラクタ
TitleScene::~TitleScene()
{
	//ここにTitleScene()が破棄されたときに呼び出したい処理を入れる

	// BGM停止
		SOUND("title_bgm")->Stop();

	// タイトルの画像を削除
	if (mpTitleImg != nullptr)
	{
		delete mpTitleImg;
		mpTitleImg = nullptr;
	}
	printf("シーンが変わりました\n");
}

//更新処理
void TitleScene::Update()
{
	//ここにTitleScene()があるときにずっと更新したい処理を入れる
	// [Enter]キーでゲームへ移行
	if (PUSH(CInput::eButton10))
	{
		//シーンをゲームに変更
		SceneManager::ChangeScene(SceneManager::STORY);
		
	}
}


//描画処理
void TitleScene::Draw()
{
	//ここにTitleScene()があるときにずっと描画したいしたい処理を入れる
	mpTitleImg->Draw();
	
}
void TitleScene::Init()
{

}
