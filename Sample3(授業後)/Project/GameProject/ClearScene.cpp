#include"ClearScene.h"
#include"SceneManager.h"

//コンストラクタ
ClearScene::ClearScene()
{
	//ここに:ClearScene()が生成されたときに呼び出したい処理を入れる

	

	printf("ゲームクリアになりました");
}

//デストラクタ
ClearScene::~ClearScene()
{
	//ここに:ClearScene()が破棄されたときに呼び出したい処理を入れる

	
	printf("シーンが変わりました\n");
}


//更新処理
void ClearScene::Update()
{
	//ここに:ClearScene()があるときにずっと更新したい処理を入れる
	if (PUSH(CInput::eButton5))
	{
		SceneManager::ChangeScene(SceneManager::GAME);
	}
}

//描画処理
void ClearScene::Draw()
{
	//ここに:ClearScene()があるときにずっと描画したいしたい処理を入れる

}

void ClearScene::Init()
{
	//ゲームオーバー、ゲームクリアのフラグをリセット（リトライ用）
	SceneManager::Instance()->isclear = false;
	SceneManager::Instance()->isover = false;
	SceneManager::Instance()->requestChange = false;

}
