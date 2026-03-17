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
#include "Hubby.h"
#include "Random.h"



#define PLAYER_COLLISIONRANGE 40.0f  //あとで消すかも プレイヤーの当たり判定
#define SHUTOME_COLLISION_RANGE 30.0f // 姑の当たり判定の大きさ
#define THROWOBJECT_COLLISION_RANGE 20.0f // 姑が投げてくるものの当たり判定の大きさ
#define SPAWN_COUNT 50
#define STAGE_WIDTH 3060 * 3

#define STAGE_BGM1 "STAGEBGM1.wav"//ステージ道中のBGM１～２好きなの選んでください
#define STAGE_BGM2 "STAGEBGM2.wav"//MP3からwavに変換しないといけない

#define LAST_STAGE_BGM1 "LASTSTAGEBGM1.wav"//ラストステージのBGM１～５好きなの選んでください
#define LAST_STAGE_BGM2 "LASTSTAGEBGM2.wav"
#define LAST_STAGE_BGM3 "LASTSTAGEBGM3.wav"
#define LAST_STAGE_BGM4 "LASTSTAGEBGM4.wav"
#define LAST_STAGE_BGM5 "LASTSTAGEBGM5.wav"


struct ObstacleData
{
	float x;
	float z;
};

ObstacleData stage2Obstacle[] =
{
	{3000,180},{3040,150},{3080,120},{3120,90},{3160,60},{3280,-30},{3320,-60},{3360,-90},{3400,-120},

	{3680,120},{3720,90},{3760,60},{3800,30},{3840,0},{3880,-30},{3920,-60},

	{4200,180},{4240,150},{4280,120},{4320,90},{4360,60},{4400,30},{4440,0},{4480,-30},{4520,-60},{4560,-90},{4600,-120},

	{4880,120},{4940,120},{5000,120},{5060,120},{5120,120},{5180,120},{4940,90},{5000,90},{5060,90},{5120,90},{5180,90},{5240,90},
	{4880,-30},{4940,-30},{5000,-30},{5060,-30},{5120,-30},{5180,-30},{4940,-60},{5000,-60},{5060,-60},{5120,-60},{5180,-60},{5240,-60},
};

ObstacleData stage3Obstacle[] =
{
	{5700,180},{5740,150},{5860,60},{5900,30},{6020,-60},{6060,-90},

	{6340,180},{6380,150},{6420,120},{6460,90},{6500,60},{6620,-30},{6660,-60},{6700,-90},{6740,-120},


	{7580,-120},{7640,-120},{7700,-120},{7760,-120},{7820,-120},{7880,-120},{7940,-120},{8000,-120},
	{7520,-90},{7640,-90},{7700,-90},{7760,-90},{7820,-90},{7880,-90},{7940,-90},

	{7300,0},{7360,0},{7420,0},{7480,0},{7520,0},{7580,0},
	{7200,30},{7260,30},{7300,30},{7360,30},{7420,30},{7480,30},{7520,30},
	{7080,60},{7140,60},{7200,60},{7260,60},{7300,60},{7360,60},{7420,60},{7480,60},
	{7020,180},{7080,180},{7140,180},{7200,180},{7260,180},{7300,180},{7360,180},{7420,180},

	{7580,180},{7620,150},{7680,120},{7720,90},{7760,60},

	{8280,180},{8320,150},{8360,120},{8400,90},{8440,60},{8480,30},{8520,0},{8560,-30},{8600,-60},{8640,-90},{8700,-120},
};

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
	

	
	
}

void GameScene::Init()//TaskManagerに追加された後に行う
{

	//カメラリセット
	Camera::Instance()->Reset();
	// フィールドを生成
	new Field();
	//UIを生成
	new Ui();
	// プレイヤーを生成
	new Player
	(CVector3D(SCREEN_WIDTH * 0.3f, 0.0f, 0.0f), PLAYER_COLLISIONRANGE);
	//姑を生成←前にいる方
	new Shutome
	(CVector3D(2600.0f, 0.0f, 0.0f), SHUTOME_COLLISION_RANGE);
	//姑を生成←ステージの一番後ろにいる方
	new Shutome
	(CVector3D(9080.0f, 0.0f, 0.0f), SHUTOME_COLLISION_RANGE);
	//回復アイテムを生成
	//new HealItem(CVector3D(5600, 0, -120));
	//new HealItem(CVector3D(7500, 0, 180));

	new Hubby(CVector3D(2600.0f, 0.0f, -50.0f), SHUTOME_COLLISION_RANGE);


	//エネミー管理クラスを生成
	//EnemyManager::Instance();
	//カメラを生成
	Camera::Instance();

	// BGM読み込み
	SOUND("stage_bgm")->Load(STAGE_BGM1, 1, false);
	// 再生（trueはループ）
	SOUND("stage_bgm")->Play(true);
	// BGM読み込み
	SOUND("last_stage_bgm")->Load(LAST_STAGE_BGM2, 1, false);
	

	printf("ゲームになりました\n");

	// 地面障害物を生成ステージ2
	int count2 = sizeof(stage2Obstacle) / sizeof(stage2Obstacle[0]);

	for (int i = 0; i < count2; i++)
	{
		new Obstacle(CVector3D(stage2Obstacle[i].x, 0, stage2Obstacle[i].z));
	}
	// 地面障害物を生成ステージ3
	int count3 = sizeof(stage3Obstacle) / sizeof(stage3Obstacle[0]);

	for (int i = 0; i < count3; i++)
	{
		new Obstacle(CVector3D(stage3Obstacle[i].x, 0, stage3Obstacle[i].z));
	}
	
	// 落下障害物をランダム生成（ステージ３用）
	for (int i = 0; i < 20; i++)
	{
		std::uniform_int_distribution<int> distX(6120, 9000);
		std::uniform_int_distribution<int> distZ(-120, 179);

		float x = distX(g_mt);
		float z = distZ(g_mt);


		// 落ちてくる障害物を生成
		new DropObstacle(DropObstacleType::EBONBORI, CVector3D(x, 400, z), PLAYER_COLLISIONRANGE);
	}
	
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

	//難易度調整処理
	Player* p = Player::GetInstance();
	if (!p) return;

	float x = p->GetPos().x;

	//プレイヤーのX座標が3060を超えると難易度2になる
	if (mDifficultyLevel == 0 && x > 3060.0f)
	{
		mDifficultyLevel = 1;
		printf("難易度アップ Lv1！\n");

		//// 皿の設定難易度2
		SetPlateGimmick(1.5f);
		//旦那生成
		new Hubby(CVector3D(5200.0f, 0.0f, -120.0f), SHUTOME_COLLISION_RANGE);
		
	}

	//プレイヤーのX座標が6120を超えると難易度3になる
	if (mDifficultyLevel == 1 && x > 6120.0f)
	{
		mDifficultyLevel = 2;
		printf("難易度アップ Lv2！\n");
		// BGM停止
		SOUND("stage_bgm")->Stop();
		// 再生（trueはループ）
		SOUND("last_stage_bgm")->Play(true);
		
		// 皿の設定難易度3
		SetPlateGimmick(0.999999999999f);
		//旦那生成
		new Hubby(CVector3D(7500.0f, 0.0f, 180.0f), SHUTOME_COLLISION_RANGE);

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