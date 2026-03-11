#pragma once
#include "EnemyBase.h"


enum class ThrowObjectType
{
	EPLATE,

};

class ThrowObject : public EnemyBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="s_pos">初期位置</param>
	ThrowObject(ThrowObjectType s_type, const CVector3D& s_pos, const float& s_collisionRange);
	~ThrowObject();

	void Update() override;
	void Render() override;



	bool Collision(ObjectBase* s_other) override;


private:


	enum class EState
	{
		ETHROWING,   // 宙に浮かんでいる状態
		EDEATH       // 消失する
	};
	void ChangeState(EState s_state);

	void StateThrowing();
	// 死亡時の更新処理
	void StateDeath();

	EState mState;

	int mStateStep;

	//アニメーションの種類
	enum class EAnimeType
	{
		ETHROWING,  // 宙に浮かんでいる状態


		ENUM
	};

	

	static TexAnimData ANIM_DATA[];
	CImage* mpImage;    //画像

	ThrowObjectType mType;

	float mMoveSpeedX;

};