#include "CharaBase.h"

// コンストラクタ
CharaBase::CharaBase()
	: CharaBase(CVector3D::zero, 0.0f)
{
}

CharaBase::CharaBase(const CVector3D& s_pos, const float& s_collisionRange)
	: ObjectBase(s_pos, s_collisionRange)
	, mMmaxHp(100)
	, mHp(mMmaxHp)
	, mIsDeath(false)
{
}

// デストラクタ
CharaBase::~CharaBase()
{
}

// ダメージを受ける
void CharaBase::TakeDamage(int s_damage)
{
	if (mHp == 0) return;	// HP0なのでスルー

	// 現在HPよりダメージ量が少ない
	if (mHp > s_damage)
	{
		mHp -= s_damage;	// そのままHPを減らす
	}
	// ダメージ量の方が大きい
	else
	{
		// HPを0にして、死亡処理を実行
		mHp = 0;
		Death();
	}
}

// 死亡処理
void CharaBase::Death()
{
	mIsDeath = true;
}
