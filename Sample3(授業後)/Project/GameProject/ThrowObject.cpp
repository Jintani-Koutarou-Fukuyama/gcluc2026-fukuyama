#include "ThrowObject.h"
#include "math.h"

#define CHIP_SIZE_WIDTH 300		// 1コマのサイズ 幅
#define CHIP_SIZE_HEIGHT 250    // 1コマのサイズ 高さ
#define CENTER_POS CVector2D(150.0f, 125.0f)	// 中心座標
#define GRAVITY 0.5f		    // 重力
#define INITIAL_VELOCITY  -22.0f //初速
#define DECELERATION -0.08f      //減速値

#define TEX_PLATE_RED "sara.png"
#define TEX_PLATE_BLUE "sara2.png"

// 投げられるもののアニメーションデータ
TexAnimData ThrowObject::ANIM_DATA[(int)EAnimeType::ENUM] =
{
	{
		new TexAnim[1]
		{ 
			{ 0, 6}
		},
		1
	},

};

ThrowObject::ThrowObject(ThrowObjectType s_type, const CVector3D& s_pos, const float& s_collisionRange)
	: EnemyBase(s_pos, s_collisionRange)
	, mpImage(nullptr)
	, mType(s_type)
	, mRotateCnt(0.0f)
{
	mTag = ETag::ETHROW;

	// スライムの画像を読み込み
	std::string imagePath;
	if (mType == ThrowObjectType::EPLATE_RED) imagePath = TEX_PLATE_RED;
	else if (mType == ThrowObjectType::EPLATE_BLUE) imagePath = TEX_PLATE_BLUE;
	//else if (m_type == SlimeType::Yellow) imagePath = "slime_c.png";
	mpImage = CImage::CreateImage
	(
		imagePath.c_str(),	// 画像ファイルのパス
		ANIM_DATA,			// アニメーションのデータ
		CHIP_SIZE_WIDTH, CHIP_SIZE_HEIGHT		// 1コマの幅と高さ
	);

	mpImage->ChangeAnimation(0);
	mpImage->SetCenter(CENTER_POS);
	mpImage->SetAng(90);
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

	
	// 宙にいる状態の時の処理
	mPos.y -= GRAVITY; //重力
	mPos.x += mMoveSpeedX; //左に飛んでいく速度
	mMoveSpeedX += sinf(DECELERATION); // 減速値を入れる

	// 回転の処理
	mpImage->SetAng(mRotateCnt);
	mRotateCnt += 0.1f;

	// 地面より下にいくと
	if (mPos.y <= 0.0f)
	{
		// 地面の座標へ戻す
		mPos.y = 0.0f;
		mMoveSpeedX = 0.0f;
		mIsGrounded = true;
	}
	//画面の左（画像の一番左）に行くと
	if (mPos.x <= 0.0f)
	{
		Kill();
	}

	//画面の下（画像の一番下）に行くと
	if (mPos.z >= 180.0f)
	{
		Kill();
	}
	//画面の上（画像の壁）に行くと
	if (mPos.z <= -120.0f)
	{
		if (mPos.x <= 850.0f)
		{
			Kill();
		}
		else if (mPos.x > 1120.0f)
		{
			Kill();

		}

		if (mPos.x >= 850.0f && mPos.x <= 1120.0f)
		{
			//壁の奥に入った時
			if (mPos.z <= -165.0f)
			{
				Kill();

			}
			if (mPos.x > 1110.0f)
			{
				Kill();

			}
		}
		if (mPos.z <= -130.0f)
		{
			//壁にめり込まないようにする
			if (mPos.x >= 860.0f && mPos.x <= 900.0f)
			{
				Kill();

			}
			if (mPos.x >= 860.0f && mPos.x <= 885.0f)
			{
				Kill();

			}
		}

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
		mMoveSpeedX = INITIAL_VELOCITY;
		mIsGrounded = false;
		mStateStep++;
		break;
		// ステップ1：地面に当たったら
	case 1:
		// 接地したら、死亡状態へ移行
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

