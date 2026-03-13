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

	// 当たり判定が有効かどうかを返す
	const bool& GetIsCollision() const;
	void SetIsCollision(bool s_iscolliion);

private:

	bool mIsCollision;
	
};
