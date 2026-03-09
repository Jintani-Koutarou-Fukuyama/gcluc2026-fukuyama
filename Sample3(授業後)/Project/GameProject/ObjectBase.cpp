#include "ObjectBase.h"
#include"Camera.h"
#define FIELD_CENTER_Z (SCREEN_HEIGHT * 0.75f)
#define FIELD_DEPTH_ANGLE 0.0f  //この値で奥行の角度を設定する
#define FIELD_DEPTH_DIR CVector2D(sinf(DtoR(FIELD_DEPTH_ANGLE)), cosf(DtoR(FIELD_DEPTH_ANGLE)))
#define TEX_SHADOW "shadow.png"

// コンストラクタ
ObjectBase::ObjectBase()
	: ObjectBase(CVector3D::zero, 0.0f)
{
}

ObjectBase::ObjectBase(const CVector3D& s_pos, const float& s_collisionRange)
	: Task((int)ETaskPrio::EOBJECT)
	, mPos(s_pos)
	, mCollisionRange(s_collisionRange)
	, mIsGrounded(true)
	, mpShadowImg(nullptr)
{
	// 影の画像を読み込み
	mpShadowImg = CImage::CreateImage(TEX_SHADOW);
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

//当たり判定の大きさを取得
const float& ObjectBase::GetCollisionRange() const
{
	return mCollisionRange;
}

// 3次元座標から2次元座標を計算
CVector2D ObjectBase::CalcScreenPos(bool s_grounded) const
{
	CVector2D ret = CVector2D::zero;

	float posZ = FIELD_CENTER_Z + mPos.z;


	// X座標はそのまま設定
	ret.x = mPos.x;
	// 通常座標を求める場合
	if (!s_grounded)
	{
		ret.y = -mPos.y;
		ret += FIELD_DEPTH_DIR * posZ;

	}
	// 高さを考慮しない地面の位置を求める場合
	else
	{

		ret += FIELD_DEPTH_DIR * posZ;
	}

	return ret + Camera::GetOffset();

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
