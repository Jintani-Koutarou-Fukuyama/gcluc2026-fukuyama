#include"GameScene.h"
#include "Field.h"
#include "Player.h"
#include"EnemyManager.h"
#include"TaskManager.h"
#include"Camera.h"
#include"SceneManager.h"
#include"Shutome.h"
#include"Ui.h"

#define PLAYER_COLLISIONRANGE 40.0f  //あとで消すかも プレイヤーの当たり判定
#define COLLISION_RANGE 20.0f // 姑の当たり判定の大きさ

GameScene::GameScene()
{
	//ここにGameScene()が生成されたときに呼び出したい処理を入れる
	
	// フィールドを生成
	new Field();
	//UIを生成
	new Ui();//ゲームシーンにUIを入れてしまったのでデストラクタするときにスコアもなくなります
	// プレイヤーを生成
	new Player
	(CVector3D(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f), PLAYER_COLLISIONRANGE);
	//姑を生成←ステージの一番後ろに配置
	new Shutome
	(CVector3D(2600.0f, 0.0f, 0.0f), COLLISION_RANGE);

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
	//ここにスコアを保存してクリアシーンまたはオーバーシーンに持っていく処理を書く必要がある

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