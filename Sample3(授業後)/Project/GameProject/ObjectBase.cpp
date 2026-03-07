#include "ObjectBase.h"
#define FIELD_CENTER_Z (SCREEN_HEIGHT * 0.75f)
#define TEXTURE "shadow.png"

// コンストラクタ
ObjectBase::ObjectBase()
	: ObjectBase(CVector3D::zero)
{
}

ObjectBase::ObjectBase(const CVector3D& s_pos)
	: Task((int)ETaskPrio::EOBJECT)
	, mPos(s_pos)
	, mIsGrounded(true)
	, mpShadowImg(nullptr)
{
	// 影の画像を読み込み
	mpShadowImg = CImage::CreateImage(TEXTURE);
	mpShadowImg->SetCenter(mpShadowImg->GetSize() * 0.5f);
}

// デストラクタ
ObjectBase::~ObjectBase()
{
	// 影の画像データを削除
	if (mpShadowImg != nullptr)
	{
		delete mpShadowImg;
		mpShadowImg = nullptr;
	}
}

// 座標を取得
const CVector3D& ObjectBase::GetPos() const
{
	return mPos;
}

// 座標を設定
void ObjectBase::SetPos(const CVector3D& s_pos)
{
	mPos = s_pos;
}

// 3次元座標から2次元座標を計算
CVector2D ObjectBase::CalcScreenPos(bool s_grounded) const
{
	CVector2D ret;

	// X座標はそのまま設定
	ret.x = mPos.x;
	// 通常座標を求める場合
	if (!s_grounded)
	{
		// Y座標は、3次元座標のY（高さ）とZ（奥行）を合わせる
		float posZ = FIELD_CENTER_Z + mPos.z;
		ret.y = -mPos.y + posZ;
	}
	// 高さを考慮しない地面の位置を求める場合
	else
	{
		// Y座標は、3次元座標のZ（奥行）のみ反映する
		ret.y = FIELD_CENTER_Z + mPos.z;
	}

	return ret;
}



// 前描画
void ObjectBase::PreRender()
{
	//オブジェクトの影を描画
	RenderShadow();
}

// 影描画
void ObjectBase::RenderShadow()
{
	// 影を地面の位置で描画
	mpShadowImg->SetPos(CalcScreenPos(true));
	mpShadowImg->Draw();
}
