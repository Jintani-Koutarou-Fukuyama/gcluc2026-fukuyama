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

}

//描画処理
void ClearScene::Draw()
{
	//ここに:ClearScene()があるときにずっと描画したいしたい処理を入れる

}