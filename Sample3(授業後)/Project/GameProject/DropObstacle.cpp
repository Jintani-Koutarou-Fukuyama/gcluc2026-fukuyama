#include "DropObstacle.h"

#define CHIP_SIZE_WIDTH 300		// 1コマのサイズ 幅
#define CHIP_SIZE_HEIGHT 250    // 1コマのサイズ 高さ
#define CENTER_POS_EHANGING CVector2D(100.0f, 140.0f)	// 中心座標(つり下がっているとき)
#define CENTER_POS_EDEATH CVector2D(80.0f, 110.0f)	// 中心座標(破壊された時)

#define GRAVITY -10.0f		    // 重力

#define TEX_DROP_OBSTACLE "bonbori.png"
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
			{ 1, 6}
		},
		1
	},
};

DropObstacle::DropObstacle(DropObstacleType s_type, const CVector3D& s_pos, const float& s_collisionRange)
	: EnemyBase(s_pos, s_collisionRange)
	, mpImage(nullptr)
	, mType(s_type)
	, mState(EState::EHANGING) 
	, mStateStep(0)
{
	mTag = ETag::EDROPOBSTACLE;


	// 落ちてくる障害物の画像を読み込み
	mpImage = CImage::CreateImage
	(
		TEX_DROP_OBSTACLE,  // 画像ファイルのパス
		ANIM_DATA,          // アニメーションのデータ
		CHIP_SIZE_WIDTH, CHIP_SIZE_HEIGHT // 1コマの幅と高さ
	);


	mpImage->SetSize(200.0f, 150.0f);
	mpImage->ChangeAnimation(0);
	mpImage->SetCenter(CENTER_POS_EHANGING);

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
	mIsGrounded = false;
	mpImage->ChangeAnimation((int)EAnimeType::EHANGING);
}

// 落ちている状態の更新処理
void DropObstacle::StateDroping()
{
	// ステップごとに処理を切り替え
	switch (mStateStep)
	{
	// ステップ 0; 落下開始
	case 0:
		
		
		mStateStep++;

		mpImage->ChangeAnimation((int)EAnimeType::EDROPING);

		break;
	// ステップ 1; 接地するまで落下
	case 1:

		mPos.y += GRAVITY;

		

		// 接地したら、消失状態へ移行
		if (mIsGrounded)
		{
			ChangeState(EState::EDEATH);

		}
		break;

	}
	
}

// 消失時の更新処理
void DropObstacle::StateDeath()
{
	SetIsCollision(false);
	mpImage->SetCenter(CENTER_POS_EDEATH);
	mpImage->ChangeAnimation((int)EAnimeType::EDEATH);

	if (!mIsGrounded)
	{
		mPos.y += GRAVITY;
	}
}

// 更新処理
void DropObstacle::Update()
{
	switch (mState)
	{
	case EState::EHANGING: StateHanging(); break;
	case EState::EDROPING: StateDroping(); break;
	case EState::EDEATH: StateDeath(); break;

	}

	// 地面より下にいくと
	if (mPos.y <= 0.0f)
	{
		// 地面の座標へ戻す
		mPos.y = 0.0f;
		// 消失状態にする
		//ChangeState(EState::EDEATH);
		mIsGrounded = true;
	}

	

	// イメージに座標を設定して、アニメーションを更新
	mpImage->SetPos(CalcScreenPos());
	mpImage->UpdateAnimation();
}

// 描画処理
void DropObstacle::Render()
{
	mpImage->Draw();
}

// 当たり判定の処理
bool DropObstacle::Collision(ObjectBase* s_other)
{

	switch (s_other->GetTag())
	{
	case ETag::EDROPOBSTACLE:
		break;
	// つり下がっている状態の時にプレーヤーが来たら
	case ETag::PLAYER:

		// プレイヤーに当たったら(プレイヤーから呼び出される)
		if (mState == EState::EHANGING)
		{
			float minDist;


			CVector3D otherPos = s_other->GetPos();

			//当たり判定の半径の合計を求める
			minDist = this->mCollisionRange + s_other->GetCollisionRange();


			// 各軸の距離を求めて、範囲外であればスルー
			if (abs(mPos.x - otherPos.x) > minDist) return false;
			//if (mPos.y < otherPos.y) return false; //プレイヤーがオブジェクトより高い場所にいれば
			if (abs(mPos.z - otherPos.z) > minDist * 0.2f) return false; //z軸は判定小さく


			// 落下させる
			ChangeState(EState::EDROPING);
			
		}
		

		break;
	}
	return false;
}

