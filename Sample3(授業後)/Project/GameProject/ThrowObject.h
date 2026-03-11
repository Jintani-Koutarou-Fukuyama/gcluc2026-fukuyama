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

	void StateIdle();

	bool Collision(ObjectBase* s_other) override;


private:

	//アニメーションの種類
	enum class EAnimeType
	{
		EIDLE,  //待機

		ENUM
	};

	int mStateStep;

	static TexAnimData ANIM_DATA[];
	CImage* mpImage;    //画像
};