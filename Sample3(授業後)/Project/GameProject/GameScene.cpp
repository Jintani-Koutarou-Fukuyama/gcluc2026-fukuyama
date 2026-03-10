#include"GameScene.h"
#include "Field.h"
#include "Player.h"
#include"EnemyManager.h"
#include"TaskManager.h"
#include"Camera.h"
#include"SceneManager.h"

#define PLAYER_COLLISIONRANGE 40.0f  //あとで消すかも


GameScene::GameScene()
{
	//ここにGameScene()が生成されたときに呼び出したい処理を入れる
	
	// フィールドを生成
	new Field();

	// プレイヤーを生成
	new Player(
		CVector3D(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f), PLAYER_COLLISIONRANGE);

	//エネミー管理クラスを生成
	EnemyManager::Instance();
	//カメラを生成
	Camera::Instance();
	printf("ゲームになりました\n");
}

GameScene::~GameScene()
{
	//ここにGameScene()が破棄されたときに呼び出したい処理を入れる
	printf("シーンが変わりました\n");
}


//更新処理
void GameScene::Update()
{
	//ここにGameScene()があるときにずっと更新したい処理を入れる

}

//描画処理
void GameScene::Draw()
{
	//ここにGameScene()があるときにずっと描画したいしたい処理を入れる
	
}