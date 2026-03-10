#include "EnemyBase.h"
#include "EnemyManager.h"

// コンストラクタ
EnemyBase::EnemyBase()
	: EnemyBase(CVector3D::zero, 0.0f)
{
}

EnemyBase::EnemyBase(const CVector3D& s_pos, const float& s_collisionRange)
	: CharaBase(s_pos, s_collisionRange)
{
	// 敵の管理クラスのリストに自身を追加
	EnemyManager::Instance()->Add(this);
}

// デストラクタ
EnemyBase::~EnemyBase()
{
	// 敵の管理クラスのリストから自身を取り除く
	EnemyManager::Instance()->Remove(this);
}

bool EnemyBase::Collision(ObjectBase* s_other)
{
	return false;
}

