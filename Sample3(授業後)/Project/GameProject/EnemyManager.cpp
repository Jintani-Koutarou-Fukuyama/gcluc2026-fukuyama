#include <math.h>
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Slime.h"

#define SPAWN_COUNT 3			// 敵生成数
#define SPAWN_INTERVAL 3.0f		// 敵を生成する間隔時間
#define SPAWN_RANGE_MIN_X 100	// X軸の敵生成範囲の最小値
#define SPAWN_RANGE_MAX_X (SCREEN_WIDTH - 100)	// X軸の敵生成範囲の最大値
#define SPAWN_RANGE_MIN_Z -200	// Z軸の敵生成範囲の最小値
#define SPAWN_RANGE_MAX_Z 100	// Z軸の敵生成範囲の最大値

#define SLIME_COLLISION_RANGE 30.0f //スライムの当たり判定の大きさ

EnemyManager* EnemyManager::msInstance = nullptr;

// コンストラクタ
EnemyManager::EnemyManager()
	:Task((int)ETaskPrio::EMANAGER)
	,mElapsedTime(0.0f)
{
}

// デストラクタ
EnemyManager::~EnemyManager()
{
	if (msInstance == this)
	{
		msInstance = nullptr;
	}
}

// インスタンス取得
EnemyManager* EnemyManager::Instance()
{
	// インスタンスがなければ、生成
	if (msInstance == nullptr)
	{
		msInstance = new EnemyManager();
	}
	return msInstance;
}

// 敵をリストに追加
void EnemyManager::Add(EnemyBase* s_enemy)
{
	mEnemies.push_back(s_enemy);
}

// 敵をリストから取り除く
void EnemyManager::Remove(EnemyBase* s_enemy)
{
	auto itr = std::remove(mEnemies.begin(), mEnemies.end(), s_enemy);
	mEnemies.erase(itr, mEnemies.end());
}

// 指定した位置から一番近い敵を取得
EnemyBase* EnemyManager::GetNearEnemy(const CVector3D& s_pos, const CVector3D& s_range)
{
	// 生成済みの全ての敵の中から一番近い敵を探す
	EnemyBase* nearEnemy = nullptr;
	float nearDist = 0.0f;
	for (EnemyBase* enemy : mEnemies)
	{
		// 各軸の距離を求めて、範囲外であればスルー
		CVector3D enemyPos = enemy->GetPos();
		if (abs(s_pos.x - enemyPos.x) > s_range.x) continue;
		if (abs(s_pos.y - enemyPos.y) > s_range.y) continue;
		if (abs(s_pos.z - enemyPos.z) > s_range.z) continue;

		// 現在の一番近い敵より近い場合は、一番近い敵に設定
		float dist = (s_pos - enemyPos).Length();
		if (nearEnemy == nullptr || dist < nearDist)
		{
			nearEnemy = enemy;
			nearDist = dist;
		}
	}
	return nearEnemy;
}

// 敵との当たり判定をする、当たっていれば位置調整をする
bool EnemyManager::Collision(CVector3D& s_pos, const float& s_collisionRange)
{

	for (EnemyBase* enemy : mEnemies)
	{
		float x, z, dist, overlap, nx, nz;
		CVector3D enemyPos = enemy->GetPos();

		//当たり判定の距離の総和(半径の合計)
		float collisionRange = s_collisionRange + enemy->GetCollisionRange();

		//当たり判定の処理、敵との距離が総和より大きければ、スキップ
		if (abs(s_pos.x - enemyPos.x) > collisionRange) continue;
		if (abs(s_pos.y - enemyPos.y) > collisionRange) continue;
		if (abs(s_pos.z - enemyPos.z) > collisionRange) continue;


		//ここから位置調整の処理
		//何をしているのかはあまりよくわからない。

		//距離を測る
		x = s_pos.x - enemyPos.x;
		z = s_pos.z - enemyPos.z;
		
		//実際の距離√x^2y^2
		dist = sqrtf(x * x + z * z);

		//重なってたら押し戻す
		overlap = collisionRange - dist;

		//正規化して押し戻し方向を決める
		nx = x / dist;
		nz = z / dist;
		
		//それぞれを半分ずつ押し戻す
		s_pos.x += nx * overlap * 0.5;
		s_pos.z += nz * overlap * 0.5;
		enemyPos.x -= nx * overlap * 0.5;
		enemyPos.z -= nz * overlap * 0.5;


		return true;



		// TODO : PlayerにCollisionメソッドを作って、ここから呼び出す。そこで当たり判定位置調整する。Tagを使って識別するため。
	}

	

}


// 更新
void EnemyManager::Update()
{
	// 現在の敵の数が、敵生成数を超えてなければ、
	if (mEnemies.size() < SPAWN_COUNT)
	{
		// 経過時間が生成間隔の時間を超えたら
		if (mElapsedTime >= SPAWN_INTERVAL)
		{
			// スライムの種類をランダムで決定
			SlimeType type = (SlimeType)Utility::Rand(0, (int)SlimeType::Num - 1);

			// スライムの位置をランダムで決定
			CVector3D pos;
			pos.x = Utility::Rand(SPAWN_RANGE_MIN_X, SPAWN_RANGE_MAX_X);
			pos.y = 0.0f;
			pos.z = Utility::Rand(SPAWN_RANGE_MIN_Z, SPAWN_RANGE_MAX_Z);

			// スライムを生成
			new Slime(type, pos, SLIME_COLLISION_RANGE);

			mElapsedTime -= SPAWN_INTERVAL;
		}

		// 経過時間を加算
		mElapsedTime += CFPS::GetDeltaTime();
	}
	// 敵生成数に達している状態
	else
	{
		mElapsedTime = 0.0f;
	}
}
