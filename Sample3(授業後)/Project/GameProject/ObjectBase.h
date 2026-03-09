#pragma once
#include"Task.h"
// 全てのオブジェクトのベースクラス
class ObjectBase:public Task
{
public:
	// コンストラクタ
	ObjectBase();
	ObjectBase(const CVector3D& s_pos, const float& s_collisionRange);
	// デストラクタ
	virtual ~ObjectBase();

	// 座標を取得
	const CVector3D& GetPos() const;
	// 座標を設定
	void SetPos(const CVector3D& s_pos);

	/// <summary>
	/// 3次元座標からスクリーン座標（2D）に変換
	/// </summary>
	/// <param name="grounded">trueならば、高さは考慮せず地面の位置を返す</param>
	/// <returns>スクリーン座標</returns>
	CVector2D CalcScreenPos(bool s_grounded = false) const;

	
	// 前描画
	void PreRender()override;

	// 影描画
	virtual void RenderShadow();

protected:
	CVector3D mPos;		// オブジェクトの座標
	bool mIsGrounded;		// 地面に接地してあるかどうか
	CImage* mpShadowImg;	// 影の画像
};