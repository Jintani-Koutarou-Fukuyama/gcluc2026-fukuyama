#pragma once
#include "EnemyBase.h"
// 姑が投げてくる物のクラス

enum class ThrowObjectType
{
	EPLATE_RED,
	EPLATE_BLUE,
	ETYAWAN,

	ENUM
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
	//  宙に浮かんでいる状態の更新処理
	void StateThrowing();
	// 消失時の更新処理
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

	ThrowObjectType mType; //姑が投げるオブジェクトのタイプ

	float mMoveSpeedX; // ものが飛んでいく速度
	float mRotateCnt;  // 回転する量を決める値
};