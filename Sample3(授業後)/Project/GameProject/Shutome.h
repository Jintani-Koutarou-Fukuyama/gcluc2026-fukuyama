#pragma once
#include "EnemyBase.h"


class Shutome : public EnemyBase
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="s_pos">初期位置</param>
	Shutome(const CVector3D& s_pos);
	~Shutome();

	void Update() override;
	void Render() override;

private:

	//アニメーションの種類
	enum class EAnimeType
	{
		EIDLE,  //待機

		ENUM
	};
	static TexAnimData ANIM_DATE[];
	CImage* mpImage;    //画像
};
