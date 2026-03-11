#include "DropObstacle.h"

#define CHIP_SIZE 300		// 1コマのサイズ
#define CENTER_POS CVector2D(150.0f, 125.0f)	// 中心座標
#define GRAVITY 0.5f		    // 重力

#define TEX_DROP_OBSTACLE ""
// 落ちてくる障害物のアニメーションデータ
TexAnimData DropObstacle::ANIM_DATA[(int)EAnimeType::ENUM] =
{
	{
		// つり下がっている状態
		new TexAnim[1]
		{
			{ 0, 6}
		},
		1
	},

	{
		// 落ちている状態
		new TexAnim[1]
		{
			{ 0, 6}
		},
		1
	},

	{
		// 消失状態
		new TexAnim[1]
		{
			{ 0, 6}
		},
		1
	},
};

DropObstacle::DropObstacle(DropObstacleType s_type, const CVector3D& s_pos, const float& s_collisionRange)
	: EnemyBase(s_pos, s_collisionRange)
	, mpImage(nullptr)
	, mType(s_type)
{
	mTag = ETag::EDROPOBSTACLE;


	// 落ちてくる障害物の画像を読み込み
	mpImage = CImage::CreateImage
	(
		TEX_DROP_OBSTACLE,  // 画像ファイルのパス
		ANIM_DATA,          // アニメーションのデータ
		CHIP_SIZE, CHIP_SIZE // 1コマの幅と高さ
	);

	mpImage->ChangeAnimation(0);
	mpImage->SetCenter(CENTER_POS);

}

DropObstacle::~DropObstacle()
{
	// H画像を削除
	if (mpImage != nullptr)
	{
		delete mpImage;
		mpImage = nullptr;
	}
}

void DropObstacle::ChangeState(EState s_state)
{
	if (mState == s_state) return;

	mState = s_state;
	mStateStep = 0;
}

//  つり下がっている状態の更新処理
void DropObstacle::StateHanging()
{
}

// 落ちている状態の更新処理
void DropObstacle::StateDroping()
{
}

// 消失時の更新処理
void DropObstacle::StateDeath()
{

}

// 更新処理
void DropObstacle::Update()
{
}

// 描画処理
void DropObstacle::Render()
{
}

// 当たり判定の処理
bool DropObstacle::Collision(ObjectBase* s_other)
{
	return false;
}

