#include"TitleScene.h"
#include"SceneManager.h"

#define TITLEIMG "仮タイトル画面.png"//←ここにタイトル画像をのせる

// コンストラクタ
TitleScene::TitleScene()
	:mpTitleImg(nullptr)
{
	// タイトル画像を読み込み
	mpTitleImg = CImage::CreateImage(TITLEIMG);
	printf("タイトルになりました");
	
}

//デストラクタ
TitleScene::~TitleScene()
{

	// タイトルの画像を削除
	if (mpTitleImg != nullptr)
	{
		delete mpTitleImg;
		mpTitleImg = nullptr;
	}
	printf("シーンが変わりました");
}

//更新処理
void TitleScene::Update()
{
	// [Enter]キーでゲームへ移行
	if (PUSH(CInput::eButton10))
	{
		//シーンをゲームに変更
		SceneManager::ChangeScene(SceneManager::GAME);

	}
}


//描画処理
void TitleScene::Draw()
{
	mpTitleImg->Draw();
	printf("描画");
}