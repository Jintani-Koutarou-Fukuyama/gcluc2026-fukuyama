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

#define SLIME_COLLISIONRANGE  30.0f // スライムの当たり判定

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

void EnemyManager::Collision(ObjectBase* s_other)
{
	for (EnemyBase* enemy : mEnemies)
	{
		// 当たり判定が無効であればスルー
		if (enemy->GetIsCollision() == false) return;

		s_other->Collision(enemy);


		// トラップなどの処理
		switch (enemy->GetTag())
		{
		case ObjectBase::ETag::EDROPOBSTACLE: // 落ちてくる障害物
			enemy->Collision(s_other);
			break;
		}
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
			new Slime(type, pos, SLIME_COLLISIONRANGE);

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
