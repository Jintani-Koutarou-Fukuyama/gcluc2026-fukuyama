#include "Hubby.h"
#include "Player.h"


#define CHIP_SIZE_WIDTH 700.0f		// 1コマのサイズ 幅
#define CHIP_SIZE_HEIGHT 800.0f		// 1コマのサイズ 高さ
#define CENTER_POS CVector2D(170.0f, 352.0f)	// 中心座標
#define MOVE_SPEED_X 7.0f
#define MOVE_SPEED_Z 5.0f

#define TEX_HUBBY "夫.png"

TexAnimData Hubby::ANIM_DATA[(int)Hubby::EAnimeType::ENUM] =
{
	// 待機アニメーション
	{
		new TexAnim[1]
		{
			{0, 6},
		},
		1
	},

	// 動いているときのアニメーション
	{
		new TexAnim[2]
		{
			{1, 15},{2, 15},
		},
		2
	},
};

Hubby::Hubby(const CVector3D& s_pos, const float& s_collisionRange)
	: EnemyBase(s_pos, s_collisionRange)
	, mState(EState::EIDLE)
	, mStateStep(0)
	, mpImage(nullptr)
	, mDestination(CVector3D::zero)
	, mMoveCnt(20)
{
	mTag = ETag::EHUBBY;

	// プレイヤーの画像を読み込み
	mpImage = CImage::CreateImage
	(
		TEX_HUBBY,	// 画像ファイルのパス
		ANIM_DATA,		// アニメーションのデータ
		CHIP_SIZE_WIDTH, CHIP_SIZE_HEIGHT	// 1コマの幅と高さ
	);
	mpImage->ChangeAnimation((int)EAnimeType::EIDLE);
	mpImage->SetCenter(CENTER_POS);

	mpImage->SetSize(CVector2D(350.0f, 380.0f));

}


Hubby::~Hubby()
{
	// 画像を削除
	if (mpImage != nullptr)
	{
		delete mpImage;
		mpImage = nullptr;
	}
}

// 現在の状態を切り替え
void Hubby::ChangeState(EState s_state)
{
	if (mState == s_state) return;

	mState = s_state;
	mStateStep = 0;
}

// 移動処理の更新
bool Hubby::UpdateMove()
{
	return false;
}

// 待機時の更新処理
void Hubby::StateIdle()
{
	mpImage->ChangeAnimation((int)EAnimeType::EIDLE);
	if (mMoveCnt <= 0) ChangeState(EState::EMOVE);

	// カウントを減らす
	mMoveCnt--;
}

// 目的地に移動中
void Hubby::StateMove()
{


	// ステップごとに処理を切り替え
	switch (mStateStep)
	{
		// ステップ0：目的地設定
	case 0:

		// 目的地を設定する
		SearchDestination();
		mStateStep++;


		mpImage->ChangeAnimation((int)EAnimeType::EMOVE);
		break;
		// ステップ1：移動する
	case 1:
		float dx, dz, dist, nx, nz;

		// x,z軸の距離を求める
		dx = mDestination.x - mPos.x;
		dz = mDestination.z - mPos.z;
		
		// √dx^2 dz^2 実際の距離を求める
		dist = sqrt(dx * dx + dz * dz);

		//正規化する
		nx = dx / dist;
		nz = dz / dist;

		// まだ近づけるのなら
		if (dist > 0)
		{
			// 近づく
			mPos.x += nx * MOVE_SPEED_X;
			mPos.z += nz * MOVE_SPEED_Z;

			// 目的地が右にあるのなら
			if (nx < 0) 
			{
				
				mpImage->SetFlipH(false);
			}
			else
			{
				// 画像を反転させる
				mpImage->SetFlipH(true);
			}
		}

		// x軸への距離が50.0より小さいなら
		if (abs(dx) < 50.0f)
		{
			ChangeState(EState::EIDLE);
			mMoveCnt = 40;

		}
		
		

		break;
	}
	
}

// 目的地を探す(目的地を設定する)
void Hubby::SearchDestination()
{
	float x, z;
	CVector3D player = Player::GetInstance()->GetPos();

	// 目的地のx座標は画面に収まるように
	x = Utility::Rand(player.x - SCREEN_WIDTH * 0.3f, player.x + SCREEN_WIDTH * 0.7f);
	// 目的地のz座標
	z = Utility::Rand(-120.0f, 180.0f);


	
	//画面の左（画像の一番左）に行くと
	if (x <= 0.0f)
	{
		//それ以上いけないようにする
		x = 0.0f;

	}

	//画面の下（画像の一番下）に行くと
	if (z >= 180.0f)
	{
		//それ以上いけないようにする
  		z = 180.0f;


	}
	//画面の上（画像の壁）に行くと
	if (z <= -120.0f)
	{
		z = -120.0f;



	}

	//画面の左（画像の一番右）に行くと
	if (x >= 7930.0f)
	{
		//それ以上いけないようにする
		x = 7930.0f;//画像の大きさが変わるたびに変更



	}

	// 目的地を設定
	mDestination = CVector3D(x, 0.0f, z);
}

void Hubby::Update()
{
	// 現在の状態に合わせて、処理を切り替える
	switch (mState)
	{
	case EState::EIDLE:		StateIdle();	break;
	case EState::EMOVE:		StateMove();	break;

	}


	// 地面より下にいくと
	if (mPos.y <= 0.0f)
	{
		// 地面の座標へ戻す
		mPos.y = 0.0f;

	}
	//画面の左（画像の一番左）に行くと
	if (mPos.x <= 0.0f)
	{
		//それ以上いけないようにする
		mPos.x = 0.0f;

	}

	//画面の下（画像の一番下）に行くと
	if (mPos.z >= 180.0f)
	{
		//それ以上いけないようにする
		mPos.z = 180.0f;


	}
	//画面の上（画像の壁）に行くと
	if (mPos.z <= -120.0f)
	{
		mPos.z = -120.0f;


	}



	//画面の左（画像の一番右）に行くと
	if (mPos.x >= 7930.0f)
	{
		//それ以上いけないようにする
		mPos.x = 7930.0f;//画像の大きさが変わるたびに変更

	}
	// イメージに座標を設定して、アニメーションを更新
	mpImage->SetPos(CalcScreenPos());
	mpImage->UpdateAnimation();


}

void Hubby::Render()
{
	mpImage->Draw();
}

bool Hubby::Collision(ObjectBase* s_other)
{
	return false;
}

