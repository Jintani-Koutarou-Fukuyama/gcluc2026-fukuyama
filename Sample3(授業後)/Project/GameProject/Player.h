#pragma once
#include "CharaBase.h"

class Player : public CharaBase
{
public:
	// コンストラクタ
	Player(const CVector3D& s_pos);
	// デストラクタ
	~Player();

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;

private:
	// 状態
	enum class EState
	{
		EIDLE,	// 待機状態
		JUMP,	// ジャンプ中
		ATTACK,	// 攻撃中
		DEATH,	// 死亡
	};
	void ChangeState(EState s_state);

	// 移動処理の更新
	bool UpdateMove();

	// 待機時の更新処理
	void StateIdle();
	// ジャンプ中の更新処理
	void StateJump();
	// 攻撃中の更新処理
	void StateAttack();
	// 死亡時の更新処理
	void StateDeath();

	// アニメーションの種類
	enum class EAnimType
	{
		IDLE,	// 待機
		MOVE,	// 移動
		DEATH,	// 死亡
		ATTACK,	// 攻撃

		NUM,
	};

	EState mState;
	int mStateStep;

	static TexAnimData ANIM_DATA[];
	CImage* mpImage;	// プレイヤーの画像

	float mMoveSpeedY;	// Y軸（高さ）の移動速度
};
