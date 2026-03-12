#pragma once
#include "EnemyBase.h"
// 落ちてくる障害物のクラス

enum class DropObstacleType
{
	EBONBORI
};


class DropObstacle : public EnemyBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="s_pos">初期位置</param>
	DropObstacle(DropObstacleType s_type, const CVector3D& s_pos, const float& s_collisionRange);
	~DropObstacle();

	void Update() override;
	void Render() override;



	bool Collision(ObjectBase* s_other) override;

private:
	enum class EState
	{
		EHANGING,   // つり下がっている状態
		EDROPING,   // 落ちている状態

		EDEATH       // 消失する
	};
	void ChangeState(EState s_state);
	//  つり下がっている状態の更新処理
	void StateHanging();
	// 落ちている状態の更新処理
	void StateDroping();
	// 消失時の更新処理
	void StateDeath();

	EState mState;

	int mStateStep;

	//アニメーションの種類
	enum class EAnimeType
	{
		EHANGING,  // つり下がっている状態
		EDROPING,   // 落ちている状態


		EDEATH,       // 消失する

		ENUM
	};



	static TexAnimData ANIM_DATA[];
	CImage* mpImage;    //画像

	DropObstacleType mType; //姑が投げるオブジェクトのタイプ

};
