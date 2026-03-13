#include"GameScene.h"
#include "Field.h"
#include "Player.h"
#include"EnemyManager.h"
#include"TaskManager.h"
#include"Camera.h"
#include"SceneManager.h"
#include"Shutome.h"
#include "ThrowObject.h"
#include"Ui.h"
#include"HealItem.h"
#include"Obstacle.h"
#include "DropObstacle.h"
#include "Random.h"



#define PLAYER_COLLISIONRANGE 40.0f  //あとで消すかも プレイヤーの当たり判定
#define SHUTOME_COLLISION_RANGE 30.0f // 姑の当たり判定の大きさ

#define STAGE_BGM1 "STAGEBGM1.wav"//ステージ道中のBGM１～２好きなの選んでください
#define STAGE_BGM2 "STAGEBGM2.wav"//MP3からwavに変換しないといけない


GameScene::GameScene()
{
	//ここにGameScene()が生成されたときに呼び出したい処理を入れる
	
	
	

}

GameScene::~GameScene()
{
	//ここにGameScene()が破棄されたときに呼び出したい処理を入れる
	

	
	// BGM停止
	SOUND("stage_bgm")->Stop();

	printf("シーンが変わりました\n");
	//ここにスコアを保存してクリアシーンまたはオーバーシーンに持っていく処理を書く必要がある

	
	
}

void GameScene::Init()//TaskManagerに追加された後に行う
{
	//カメラリセット
	Camera::Instance()->Reset();
	// フィールドを生成
	new Field();
	//UIを生成
	new Ui();//ゲームシーンにUIを入れてしまったのでデストラクタするときにスコアもなくなります
	// プレイヤーを生成
	new Player
	(CVector3D(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f), PLAYER_COLLISIONRANGE);
	//姑を生成←ステージの一番後ろに配置
	new Shutome
	(CVector3D(2600.0f, 0.0f, 0.0f), SHUTOME_COLLISION_RANGE);
	//回復アイテムを生成
	new HealItem(CVector3D(100, 0, 0));
	//姑が投げてくる物を生成
	new ThrowObject(ThrowObjectType::EPLATE_RED, CVector3D(1300, 300.0f, -110.0f), SHUTOME_COLLISION_RANGE);

	//エネミー管理クラスを生成
	EnemyManager::Instance();
	//カメラを生成
	Camera::Instance();
	// BGM読み込み
	SOUND("stage_bgm")->Load(STAGE_BGM1, 1, false);
	// 再生（trueはループ）
	SOUND("stage_bgm")->Play(true);

	printf("ゲームになりました\n");

	// 障害物をランダム生成
	for (int i = 0; i < 10; i++)
	{
		float x = rand() % 2000 + 800;
		float z = rand() % 300 - 120;

		new Obstacle(CVector3D(x, 0, z));
	}

	// 落ちてくるをランダム生成（ステージ２用）
	for (int i = 0; i < 10; i++)
	{
		std::uniform_int_distribution<int> distX(2800, 5200);
		std::uniform_int_distribution<int> distZ(-120, 179);

		float x = distX(g_mt);
		float z = distZ(g_mt);


		// 落ちてくる障害物を生成
		new DropObstacle(DropObstacleType::EBONBORI, CVector3D(x, 400, z), PLAYER_COLLISIONRANGE);
	}
	
	// 落ちてくるをランダム生成（ステージ３用）
	for (int i = 0; i < 15; i++)
	{
		std::uniform_int_distribution<int> distX(5200, 7500);
		std::uniform_int_distribution<int> distZ(-120, 179);

		float x = distX(g_mt);
		float z = distZ(g_mt);


		// 落ちてくる障害物を生成
		new DropObstacle(DropObstacleType::EBONBORI, CVector3D(x, 400, z), PLAYER_COLLISIONRANGE);
	}
	// 姑が投げてくるものをランダム生成 テスト用（TODO:後で消す）
	for (int i = 0; i < 10; i++)
	{

		//めちゃくちゃてきとう
		float x = rand() % 2600;
		float y = rand() % 200;
		float z = rand() % 120;


		new ThrowObject((ThrowObjectType)(i % 2), CVector3D(x, y, z), PLAYER_COLLISIONRANGE);
	}
}

//更新処理
void GameScene::Update()
{
	//ここにGameScene()があるときにずっと更新したい処理を入れる

	//難易度調整処理
	Player* p = Player::GetInstance();
	if (!p) return;

	float x = p->GetPos().x;

	//プレイヤーのX座標が2500を超えると難易度2になる
	if (mDifficultyLevel == 0 && x > 2500.0f)
	{
		mDifficultyLevel = 1;
		printf("難易度アップ Lv1！\n");
	}

	//プレイヤーのX座標が5200を超えると難易度3になる
	if (mDifficultyLevel == 1 && x > 5200.0f)
	{
		mDifficultyLevel = 2;
		printf("難易度アップ Lv2！\n");

	}

}

//描画処理
void GameScene::Draw()
{
	//ここにGameScene()があるときにずっと描画したいしたい処理を入れる
	
}