#include"GameScene.h"
#include "Field.h"
#include "Player.h"
#include"EnemyManager.h"
#include"TaskManager.h"
#include"Camera.h"
#include"SceneManager.h"


GameScene::GameScene()
{
	// フィールドを生成
	new Field();

	// プレイヤーを生成
	new Player(
		CVector3D(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f));

	//エネミー管理クラスを生成
	EnemyManager::Instance();
	//カメラを生成
	Camera::Instance();
	printf("ゲームになりました");
}

GameScene::~GameScene()
{
	printf("シーンが変わりました");
}


//更新処理
void GameScene::Update()
{

}

//描画処理
void GameScene::Draw()
{
	
}