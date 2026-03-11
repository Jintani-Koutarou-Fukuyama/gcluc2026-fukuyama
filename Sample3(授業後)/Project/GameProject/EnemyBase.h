#pragma once
#include "CharaBase.h"

// 敵のベースクラス
class EnemyBase : public CharaBase
{
public:
	// コンストラクタ
	EnemyBase();
	EnemyBase(const CVector3D& s_pos, const float& s_collisionRamge);
	// デストラクタ
	virtual ~EnemyBase();

	bool Collision(ObjectBase* s_other) override;

	
};
