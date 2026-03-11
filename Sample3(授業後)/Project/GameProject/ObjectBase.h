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
	//当たり判定を取得
	const float &GetCollisionRange() const;
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

	// Collision(衝突先のポインタ)
	// 当たり判定の処理を書く
	virtual bool Collision(ObjectBase* s_other);

	// オブジェクトの識別タグ
	enum class ETag
	{
		ENONE,     // 初期状態
		ESHUTOME,  // 姑
		ETHROW,    // 姑が投げてくるもの
		EHEALITEM, // 回復薬
		EDROPOBSTACLE // 落ちてくる障害物
	};


	//タグを返す
	const ETag GetTag() const;

protected:
	CVector3D mPos;		// オブジェクトの座標
	float mCollisionRange; //当たり判定の大きさ
	bool mIsGrounded;		// 地面に接地してあるかどうか
	CImage* mpShadowImg;	// 影の画像

	ETag mTag;  //当たり判定の時に使う識別タグ
};