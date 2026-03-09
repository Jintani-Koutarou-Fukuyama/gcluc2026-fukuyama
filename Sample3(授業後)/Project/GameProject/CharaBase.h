#pragma once
#include "ObjectBase.h"

// キャラクターのベースクラス
class CharaBase : public ObjectBase
{
public:
	// コンストラクタ
	CharaBase();
	CharaBase(const CVector3D& s_pos, const float& s_collisionRange);
	// デストラクタ
	virtual ~CharaBase();

	// ダメージを受ける
	void TakeDamage(int s_damage);
	// 死亡処理
	virtual void Death();

protected:
	int mMmaxHp;		// 最大HP
	int mHp;			// 現在HP
	bool mIsDeath;		// 死亡フラグ
};
