#pragma once
#include "EnemyBase.h"

class Hubby : public EnemyBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="s_pos">初期位置</param>
	Hubby(const CVector3D& s_pos, const float& s_collisionRange);
	~Hubby();

	void Update() override;
	void Render() override;

	bool Collision(ObjectBase* s_other) override;


private:
	// 状態
	enum class EState
	{
		EIDLE,	    // 待機状態
		EMOVE       // 目的に移動中

	};
	void ChangeState(EState s_state);

	// 移動処理の更新
	bool UpdateMove();

	// 待機時の更新処理
	void StateIdle();
	// 目的地に移動中
	void StateMove();


	// 目的地を探す
	void SearchDestination();

	//アニメーションの種類
	enum class EAnimeType
	{
		EIDLE,  //待機
		EMOVE,

		ENUM
	};

	int mStateStep;
	EState mState;

	static TexAnimData ANIM_DATA[];
	CImage* mpImage;    //画像

	CVector3D mDestination;  // 目的地
	int mMoveCnt;            // 次の行動へのカウントダウン用
};
