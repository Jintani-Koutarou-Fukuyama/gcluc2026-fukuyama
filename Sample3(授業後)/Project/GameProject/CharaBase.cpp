#include "CharaBase.h"

// コンストラクタ
CharaBase::CharaBase()
	: CharaBase(CVector3D::zero)
{
}

CharaBase::CharaBase(const CVector3D& s_pos)
	: ObjectBase(s_pos)
	, mMmaxHp(5)
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

int CharaBase::GetHp() const
{
	return mHp;
}

int CharaBase::GetMaxHp() const
{
	return mMmaxHp;
}
