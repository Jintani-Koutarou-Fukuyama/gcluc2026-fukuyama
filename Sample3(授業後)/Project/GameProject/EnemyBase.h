#pragma once
#include "CharaBase.h"

// 敵のベースクラス
class EnemyBase : public CharaBase
{
public:
	// コンストラクタ
	EnemyBase();
	EnemyBase(const CVector3D& s_pos);
	// デストラクタ
	virtual ~EnemyBase();

private:
};
