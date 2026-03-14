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
#define THROWOBJECT_COLLISION_RANGE 20.0f // 姑が投げてくるものの当たり判定の大きさ
#define SPAWN_COUNT 50
#define STAGE_WIDTH 2666 * 3

#define STAGE_BGM1 "STAGEBGM1.wav"//ステージ道中のBGM１～２好きなの選んでください
#define STAGE_BGM2 "STAGEBGM2.wav"//MP3からwavに変換しないといけない

#define LAST_STAGE_BGM1 "LASTSTAGEBGM1.wav"//ラストステージのBGM１～５好きなの選んでください
#define LAST_STAGE_BGM2 "LASTSTAGEBGM2.wav"
#define LAST_STAGE_BGM3 "LASTSTAGEBGM3.wav"
#define LAST_STAGE_BGM4 "LASTSTAGEBGM4.wav"
#define LAST_STAGE_BGM5 "LASTSTAGEBGM5.wav"


GameScene::GameScene()
	: mElapsedTime(0.0f)
	, mInterval(0.0f)
{
	//ここにGameScene()が生成されたときに呼び出したい処理を入れる
	
    // 皿の設定難易度1
	SetPlateGimmick(2.0f);
	

}

GameScene::~GameScene()
{
	//ここにGameScene()が破棄されたときに呼び出したい処理を入れる
	

	
	// BGM停止
	SOUND("stage_bgm")->Stop();
	SOUND("last_stage_bgm")->Stop();
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
	(CVector3D(SCREEN_WIDTH * 0.3f, 0.0f, 0.0f), PLAYER_COLLISIONRANGE);
	//姑を生成←前にいる方
	new Shutome
	(CVector3D(2600.0f, 0.0f, 0.0f), SHUTOME_COLLISION_RANGE);
	//姑を生成←ステージの一番後ろにいる方
	new Shutome
	(CVector3D(7900.0f, 0.0f, 0.0f), SHUTOME_COLLISION_RANGE);
	//回復アイテムを生成
	new HealItem(CVector3D(100, 0, 0));


	//エネミー管理クラスを生成
	EnemyManager::Instance();
	//カメラを生成
	Camera::Instance();

	// BGM読み込み
	SOUND("stage_bgm")->Load(STAGE_BGM1, 1, false);
	// 再生（trueはループ）
	SOUND("stage_bgm")->Play(true);
	// BGM読み込み
	SOUND("last_stage_bgm")->Load(LAST_STAGE_BGM2, 1, false);
	

	printf("ゲームになりました\n");

	// 落下障害物をランダム生成ステージ2
	for (int i = 0; i < 10; i++)
	{
		float x = rand() % 2000 + 2800;
		float z = rand() % 300 - 120;

		new Obstacle(CVector3D(x, 0, z));
	}
	// 落下障害物をランダム生成ステージ3
	for (int i = 0; i < 15; i++)
	{
		float x = rand() % 2000 + 5200;
		float z = rand() % 300 - 120;

		new Obstacle(CVector3D(x, 0, z));
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
	new DropObstacle(DropObstacleType::EBONBORI, CVector3D(200, 400, 100), PLAYER_COLLISIONRANGE);
}

// 皿の設定(間隔を設定する)
void GameScene::SetPlateGimmick(float s_interval)
{

	mInterval = s_interval;

}

//　皿を生成する
void GameScene::PopPlate()
{
	// 現在の敵の数が、敵生成数を超えてなければ、
	if (mSpawnCnt < SPAWN_COUNT)
	{
		// 画面外にスポーン地点を設定
		float spawnPointX = Player::GetInstance()->GetPos().x + SCREEN_WIDTH + 20.0f;
		// 画面の端が画面に映っているなら生成しない
		if (spawnPointX >= STAGE_WIDTH) return;

		// 経過時間が生成間隔の時間を超えたら
		if (mElapsedTime >= mInterval)
		{
			// 種類をランダムで生成する
			ThrowObjectType type = (ThrowObjectType)Utility::Rand(0, (int)ThrowObjectType::ENUM - 1);

			// 位置をランダムで決定する
			CVector3D pos;
			pos.x = Utility::Rand(spawnPointX, spawnPointX + 50.0f);
			pos.y = Utility::Rand(200.0f, 250.0f);
			pos.z = Utility::Rand(-120.0f, 180.0f);

			// 生成する
			new ThrowObject(type, pos, THROWOBJECT_COLLISION_RANGE);



			mElapsedTime -= mInterval;
		}

		// 経過時間を加算
		mElapsedTime += CFPS::GetDeltaTime();
	}
	// 生成数に達している状態
	else
	{
		mElapsedTime = 0.0f;
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

	//プレイヤーのX座標が2666を超えると難易度2になる
	if (mDifficultyLevel == 0 && x > 2666.0f)
	{
		mDifficultyLevel = 1;
		printf("難易度アップ Lv1！\n");

		//// 皿の設定難易度2
		SetPlateGimmick(1.5f);
		
	}

	//プレイヤーのX座標が5332を超えると難易度3になる
	if (mDifficultyLevel == 1 && x > 5332.0f)
	{
		mDifficultyLevel = 2;
		printf("難易度アップ Lv2！\n");
		// BGM停止
		SOUND("stage_bgm")->Stop();
		// 再生（trueはループ）
		SOUND("last_stage_bgm")->Play(true);
		
		// 皿の設定難易度3
		SetPlateGimmick(0.999999999999f);
	}
	
	// 皿を生成する
	for (int i = 0; i < 2; i++)
	{
		PopPlate();
	}
	
}

//描画処理
void GameScene::Draw()
{
	//ここにGameScene()があるときにずっと描画したいしたい処理を入れる
	
}