#include"OverScene.h"
#include"SceneManager.h"

#define OVERIMG "ゲームオーバー.png"//←ここにゲームオーバー画像をのせる

//コンストラクタ
OverScene::OverScene()
	:mpTitleImg(nullptr)
{
	// タイトル画像を読み込み
	mpTitleImg = CImage::CreateImage(OVERIMG);
	//ここにOverScene()が生成されたときに呼び出したい処理を入れる
	SOUND("over_se")->Load("gameover.wav", 1, false);
	SOUND("over_se")->Play(false);
	printf("ゲームオーバーになりました\n");
}

//デストラクタ
OverScene::~OverScene()
{
	//ここにOverScene()が破棄されたときに呼び出したい処理を入れる
	
	// ゲームオーバーの画像を削除
	if (mpTitleImg != nullptr)
	{
		delete mpTitleImg;
		mpTitleImg = nullptr;
	}
	printf("シーンが変わりました\n");
}


//更新処理
void OverScene::Update()
{
	//ここにOverScene()があるときにずっと更新したい処理を入れる
	
	// [Enter]キーでゲームへ移行
	if (PUSH(CInput::eButton10))
	{
		//シーンをゲームに変更
		SceneManager::ChangeScene(SceneManager::GAME);

	}
}

//描画処理
void OverScene::Draw()
{
	//ここにOverScene()があるときにずっと描画したいしたい処理を入れる
	mpTitleImg->Draw();
}
void OverScene::Init()
{
	//ゲームオーバー、ゲームクリアのフラグをリセット（リトライ用）
	SceneManager::Instance()->isclear = false;
	SceneManager::Instance()->isover = false;
	SceneManager::Instance()->requestChange = false;

}
