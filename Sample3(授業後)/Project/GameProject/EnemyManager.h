#pragma once
#include"Task.h"
class EnemyBase;

// 敵管理クラス
class EnemyManager:public Task
{
public:
	// インスタンス取得
	static EnemyManager* Instance();

	// 敵をリストに追加
	void Add(EnemyBase* s_enemy);
	// 敵をリストから取り除く
	void Remove(EnemyBase* s_enemy);

	// 指定した位置から一番近い敵を取得
	EnemyBase* GetNearEnemy(const CVector3D& s_pos, const CVector3D& s_range);

	bool Collision(CVector3D& s_pos, const float& s_collisionRange);

	// 更新
	void Update()override;

private:
	// コンストラクタ
	EnemyManager();
	// デストラクタ
	~EnemyManager();

	// インスタンス
	static EnemyManager* msInstance;
	// 生成済みのエネミーのリスト
	std::vector<EnemyBase*> mEnemies;

	float mElapsedTime;	// 経過時間計測用
};
