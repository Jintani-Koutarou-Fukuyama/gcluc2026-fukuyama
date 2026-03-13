#include"ClearScene.h"
#include"SceneManager.h"


#define CREARIMG "CrearScene.png"//←ここにゲームクリア画像をのせる

//コンストラクタ
ClearScene::ClearScene()
	:mpTitleImg(nullptr)
{
	//ここに:ClearScene()が生成されたときに呼び出したい処理を入れる

	
	// タイトル画像を読み込み
	mpTitleImg = CImage::CreateImage(CREARIMG);
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
}

//描画処理
void ClearScene::Draw()
{
	//ここに:ClearScene()があるときにずっと描画したいしたい処理を入れる
	mpTitleImg->Draw();
}

void ClearScene::Init()
{
	//ゲームオーバー、ゲームクリアのフラグをリセット（リトライ用）
	SceneManager::Instance()->isclear = false;
	SceneManager::Instance()->isover = false;
	SceneManager::Instance()->requestChange = false;

}
