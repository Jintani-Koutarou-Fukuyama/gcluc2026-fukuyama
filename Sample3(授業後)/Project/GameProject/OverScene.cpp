#include"OverScene.h"
#include"SceneManager.h"


//コンストラクタ
OverScene::OverScene()
{
	//ここにOverScene()が生成されたときに呼び出したい処理を入れる
	printf("ゲームオーバーになりました");
}

//デストラクタ
OverScene::~OverScene()
{
	//ここにOverScene()が破棄されたときに呼び出したい処理を入れる

	printf("シーンが変わりました\n");
}


//更新処理
void OverScene::Update()
{
	//ここにOverScene()があるときにずっと更新したい処理を入れる

}

//描画処理
void OverScene::Draw()
{
	//ここにOverScene()があるときにずっと描画したいしたい処理を入れる

}