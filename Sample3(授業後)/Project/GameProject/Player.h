#pragma once
#include "CharaBase.h"
// プレイヤー(嫁)のクラス

class Player : public CharaBase
{
public:
	// コンストラクタ
	Player(const CVector3D& s_pos, const float& s_collisionRange);
	// デストラクタ
	~Player();

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;



	static Player* GetInstance();
	
	bool Collision(ObjectBase* s_other) override;
private:

	static Player* mspInstance;
	// 状態
	enum class EState
	{
		EIDLE,	    // 待機状態
		EJUMP,	    // ジャンプ中
		EATTACK,	// 攻撃中
		EDEATH, 	// 死亡
		ESTUN       //スタン状態
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
	// スタン状態の更新処理
	void StateStun();

	// アニメーションの種類
	enum class EAnimType
	{
		EIDLE,	// 待機
		EMOVE,	// 移動
		EDEATH,	// 死亡
		EATTACK,	// 攻撃
		ESTUN,   //スタン状態
		EJUNP,

		ENUM,
	};

	EState mState;
	int mStateStep;

	static TexAnimData ANIM_DATA[];
	CImage* mpImage;	// プレイヤーの画像

	float mMoveSpeedY;	// Y軸（高さ）の移動速度

	bool mIsStun;   //スタン状態を判別する
	CVector3D mKnockbackdistance; //ノックバックする距離
	int mInvincibilityCnt; //無敵時間をカウントするカウンター
	bool isDead = false;//死亡フラグ

};
