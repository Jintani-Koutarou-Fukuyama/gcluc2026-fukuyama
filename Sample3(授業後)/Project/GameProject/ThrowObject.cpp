#include "ThrowObject.h"

#define CHIP_SIZE 256		// 1コマのサイズ
#define CENTER_POS CVector2D(128.0f, 184.0f)	// 中心座標

#define TEX_PLATE "slime_a.png"

// スライムのアニメーションデータ
TexAnimData ThrowObject::ANIM_DATA[(int)EAnimeType::ENUM] =
{
	{
		new TexAnim[4]
		{
			{ 0, 6}, { 1, 6},
			{ 2, 6}, { 3, 6},
		},
		4
	},

};

ThrowObject::ThrowObject(ThrowObjectType s_type, const CVector3D& s_pos, const float& s_collisionRange)
	: EnemyBase(s_pos, s_collisionRange)
	, mpImage(nullptr)
	, mType(s_type)
{
	mTag = ETag::ETHROW;

	// スライムの画像を読み込み
	std::string imagePath;
	if (mType == ThrowObjectType::EPLATE) imagePath = TEX_PLATE;
	//else if (m_type == SlimeType::Green) imagePath = "slime_b.png";
	//else if (m_type == SlimeType::Yellow) imagePath = "slime_c.png";
	mpImage = CImage::CreateImage
	(
		imagePath.c_str(),	// 画像ファイルのパス
		ANIM_DATA,			// アニメーションのデータ
		CHIP_SIZE, CHIP_SIZE		// 1コマの幅と高さ
	);

	mpImage->ChangeAnimation(0);
	mpImage->SetCenter(CENTER_POS);
	mpImage->SetFlipH(true);
}

ThrowObject::~ThrowObject()
{
	// 画像データを削除
	delete mpImage;
}

void ThrowObject::Update()
{
	// 状態に合わせて、更新処理を切り替える
	switch (mState)
	{
	case EState::ETHROWING:	StateThrowing();	break;
	case EState::EDEATH: StateDeath(); break;

	}

	

	mPos.y -= 5.90; //重力
	mPos.x -= mMoveSpeedX; //左に飛んでいく
	mMoveSpeedX -= 1.0f; // 減速値を入れる

	// 地面より下にいくと
	if (mPos.y <= 0.0f)
	{
		// 地面の座標へ戻す
		mPos.y = 0.0f;
		mMoveSpeedX = 0.0f;
		mIsGrounded = true;
	}


	// イメージに座標を設定して、アニメーションを更新
	mpImage->SetPos(CalcScreenPos());
	mpImage->UpdateAnimation();
}

void ThrowObject::Render()
{
	mpImage->Draw();
}

bool ThrowObject::Collision(ObjectBase* s_other)
{
	return false;
}

void ThrowObject::StateThrowing()
{
	// ステップごとに処理を切り替え
	switch (mStateStep)
	{
		// ステップ0：開始
	case 0:
		// X軸（幅）初速を設定し、
		// 接地状態を解除する
		mMoveSpeedX = 50;
		mIsGrounded = false;
		mStateStep++;
		break;
		// ステップ1：ジャンプ終了
	case 1:
		// 接地したら、待機状態へ移行
		if (mIsGrounded)
		{
			ChangeState(EState::EDEATH);
		}
		break;
	}

}

void ThrowObject::StateDeath()
{
	Kill();
}

void ThrowObject::ChangeState(EState s_state)
{
	if (mState == s_state) return;

	mState = s_state;
	mStateStep = 0;
}

