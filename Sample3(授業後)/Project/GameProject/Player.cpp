#include "Player.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "SceneManager.h"
#include"Camera.h"

#define CHIP_SIZE 384		// 1コマのサイズ
#define CENTER_POS CVector2D(192.0f, 328.0f)	// 中心座標
#define MOVE_SPEED_X 5.0f	// 横方向の移動速度
#define MOVE_SPEED_Z 3.0f	// 奥方向の移動速度
#define JUMP_SPEED 15.0f	// ジャンプ速度
#define GRAVITY -1.0f		// 重力
#define ATTACK_INDEX 2		// 攻撃が発生するアニメーションの番号
#define ATTACK_RANGE CVector3D(300.0f, 10.0f, 50.0f)	// 攻撃範囲
#define KNOCKBACK_RAITO 1.2f  //ノックバック距離、ノックバックの距離を決める
#define INVINCIBILITY_TIME 10 //無敵時間

#define TEX_PLAYER "player.png"

Player* Player::mspInstance = nullptr;
// プレイヤーのアニメーションデータの前宣言
TexAnimData Player::ANIM_DATA[(int)EAnimType::ENUM] =
{
	// 待機アニメーション
	{
		new TexAnim[6]
		{
			{0, 6}, {1, 6}, {2, 6},
			{3, 6}, {4, 6}, {5, 6},
		},
		6
	},
	// 移動アニメーション
	{
		new TexAnim[6]
		{
			{6, 6}, {7, 6}, {8, 6},
			{9, 6}, {10, 6}, {11, 6},
		},
		6
	},
	// 死亡アニメーション
	{
		new TexAnim[3]
		{
			{12, 12},
			{13, 12},
			{14, 12},
		},
		3
	},
	// 攻撃アニメーション
	{
		new TexAnim[4]
		{
			{18, 6},
			{19, 6},
			{20, 6},
			{21, 6},
		},
		4
	},
	// スタンアニメーション
	{
		new TexAnim[1]
		{
			{12, 20},   //次の画像までの待機フレーム(2番目の値)でスタンの長さが変わる
		},
		1
	}
};


// コンストラクタ
Player::Player(const CVector3D& s_pos, const float& s_collisionRange)
	: CharaBase(s_pos, s_collisionRange)
	, mState(EState::EIDLE)
	, mStateStep(0)
	, mpImage(nullptr)
	, mIsStun(false)
	, mKnockbackdistance(CVector3D::zero)
	, mInvincibilityCnt(0)
{
	mHp = 5;

	// プレイヤーの画像を読み込み
	mpImage = CImage::CreateImage
	(
		TEX_PLAYER,	// 画像ファイルのパス
		ANIM_DATA,		// アニメーションのデータ
		CHIP_SIZE, CHIP_SIZE	// 1コマの幅と高さ
	);
	mpImage->ChangeAnimation((int)EAnimType::EIDLE);
	mpImage->SetCenter(CENTER_POS);
	mspInstance = this;
}

// デストラクタ
Player::~Player()
{
	// 画像データを削除
	delete mpImage;
}

// 現在の状態を切り替え
void Player::ChangeState(EState s_state)
{
	if (mState == s_state) return;

	mState = s_state;
	mStateStep = 0;
}

// 移動処理の更新
bool Player::UpdateMove()
{
	bool isMove = false;
	// Aキーを押している間
	if (HOLD(CInput::eButton6))
	{
		// 左方向へ移動
		mPos.x -= MOVE_SPEED_X;
		mpImage->SetFlipH(true);
		isMove = true;
	}
	// Dキーを押している間
	else if (HOLD(CInput::eButton9))
	{
		// 右方向へ移動
		mPos.x += MOVE_SPEED_X;
		mpImage->SetFlipH(false);
		isMove = true;
	}
	// Wキーを押している間
	if (HOLD(CInput::eButton7))
	{
		// 奥方向へ移動
		mPos.z -= MOVE_SPEED_Z;
		isMove = true;
	}
	// Sキーを押している間
	else if (HOLD(CInput::eButton8))
	{
		// 手前方向へ移動
		mPos.z += MOVE_SPEED_Z;
		isMove = true;
	}

	return isMove;
}

// 待機時の更新処理
void Player::StateIdle()
{
	// 移動処理
	bool isMove = UpdateMove();

	// 移動状態に合わせて、アニメーションを切り替え
	EAnimType anim = isMove ? EAnimType::EMOVE : EAnimType::EIDLE;
	mpImage->ChangeAnimation((int)anim);

	// [SPACE]キーでジャンプ状態へ移行
	if (PUSH(CInput::eButton5))
	{
		ChangeState(EState::EJUMP);
	}
	// [X]キーで攻撃状態へ移行
	else if (PUSH(CInput::eButton2))
	{
		ChangeState(EState::EATTACK);
	}

	if (mInvincibilityCnt >= 1)
	{
		mInvincibilityCnt--;
	}
}

// ジャンプ中の更新処理
void Player::StateJump()
{
	// ステップごとに処理を切り替え
	switch(mStateStep)
	{
		// ステップ0：ジャンプ開始
		case 0:
			// Y軸（高さ）の移動速度にジャンプを速度を設定し、
			// 接地状態を解除する
			mMoveSpeedY = JUMP_SPEED;
			mIsGrounded = false;
			mStateStep++;
			break;
		// ステップ1：ジャンプ終了
		case 1:
			// 接地したら、待機状態へ移行
			if (mIsGrounded)
			{
				ChangeState(EState::EIDLE);
			}
			break;
	}

	// 移動処理
	bool isMove = UpdateMove();
	mpImage->ChangeAnimation((int)EAnimType::EIDLE);
}

// 攻撃中の更新処理
void Player::StateAttack()
{
	// ステップごとに処理を切り替え
	switch (mStateStep)
	{
		// ステップ0：攻撃アニメーションに切り替え
		case 0:
			mpImage->ChangeAnimation((int)EAnimType::EATTACK, false);
			mStateStep++;
			break;
			// ステップ1：攻撃判定
		case 1:
			// 攻撃アニメーションが攻撃タイミングまで進めば
			if (mpImage->GetIndex() >= ATTACK_INDEX)
			{
				// 一番近い敵にダメージを与える
				EnemyBase* enemy = EnemyManager::Instance()->GetNearEnemy(mPos, ATTACK_RANGE);
				if (enemy != nullptr)
				{
					enemy->TakeDamage(100);
				}
				mStateStep++;
			}
			break;
			// ステップ2：アニメーション終了待ち
		case 2:
			// 攻撃アニメーションが終了したら、待機状態へ移行
			if (mpImage->CheckAnimationEnd())
			{
				ChangeState(EState::EIDLE);
			}
			break;
	}
}

// 死亡時の更新処理
void Player::StateDeath()
{
	SceneManager::ChangeScene(SceneManager::ESCENE::OVER);
}

// スタン時の更新処理
void Player::StateStun()
{
	// ステップごとに処理を切り替え
	switch (mStateStep)
	{
		// ステップ0：攻撃アニメーションに切り替え
	case 0:
		mpImage->ChangeAnimation((int)EAnimType::ESTUN, false);
		mStateStep++;

		
		break;

		// ステップ2：アニメーション終了待ち
	case 1:
		if (mIsStun)
		{
			// ノックバック距離を位置に加算する
			mPos += mKnockbackdistance;
		}
		

		// 攻撃アニメーションが終了したら、待機状態へ移行
		if (mpImage->CheckAnimationEnd())
		{
			
			ChangeState(EState::EIDLE);
			if (mIsStun)
			{
				mIsStun = false;
			}
			
			
		}
		
		break;

	}
}

// 更新処理
void Player::Update()
{
	//死亡状態でシーンチェンジ
	if (mHp <= 0 && mState != EState::EDEATH)
	{
		ChangeState(EState::EDEATH);
	}

	if (mInvincibilityCnt <= 0)
	{
		//敵との当たり判定
		EnemyManager::Instance()->Collision(this);

	}
	

	// 現在の状態に合わせて、処理を切り替える
	switch (mState)
	{
	case EState::EIDLE:		StateIdle();	break;
	case EState::EJUMP:		StateJump();	break;
	case EState::EATTACK:	StateAttack();	break;
	case EState::EDEATH:	StateDeath();	break;
	case EState::ESTUN:     StateStun();    break;
	}

	

	// Y軸（高さ）の移動を座標に反映
	mPos.y += mMoveSpeedY;
	mMoveSpeedY += GRAVITY;	// Y軸の移動速度に重力を加算
	// 地面より下にいくと
	if (mPos.y <= 0.0f)
	{
		// 地面の座標へ戻す
		mPos.y = 0.0f;
		mMoveSpeedY = 0.0f;
		mIsGrounded = true;
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
		if (mPos.x <= 850.0f)
		{
			//それ以上いけないようにする
			mPos.z = -120.0f;
		}
		else if (mPos.x > 1120.0f)
		{
			//それ以上いけないようにする
			mPos.z = -120.0f;
		}
		
		if (mPos.x >= 850.0f && mPos.x <= 1120.0f)
		{
			//壁の奥に入った時
			if (mPos.z <= -165.0f)
			{
				//それ以上いけないようにする
				mPos.z = -165.0f;
			}
			if (mPos.x > 1110.0f)
			{
				//それ以上いけないようにする
				mPos.x = 1110.0f;
			}
		}
		if (mPos.z <= -130.0f)
		{
			//壁にめり込まないようにする
			if (mPos.x >= 860.0f && mPos.x <= 900.0f)
			{
				mPos.z = -155.0f;
			}
			if (mPos.x >= 860.0f && mPos.x <= 885.0f)
			{
				mPos.z = -145.0f;
			}
		}
		
	}
	


	//画面の左（画像の一番右）に行くと
	if (mPos.x >= 2600.0f)
	{
		//それ以上いけないようにする
		mPos.x = 2600.0f;//画像の大きさが変わるたびに変更
	}
	// イメージに座標を設定して、アニメーションを更新
	mpImage->SetPos(CalcScreenPos());
	mpImage->UpdateAnimation();

	DebugPrint::Print("プレイヤー位置：%.2f, %.2f, %.2f", mPos.x, mPos.y, mPos.z);

	Camera::SetTargetPos(mPos);

}

// 描画処理
void Player::Render()
{
	mpImage->Draw();
}

Player* Player::GetInstance()
{
	return mspInstance;
}

// 当たり判定
bool Player::Collision(ObjectBase* s_other)
{
	
	if (mIsStun == false) 
	{
		// TODO: Z軸の当たり判定が大きいかもしれない。直方体型にする


		float dx, dz, dist, minDist, overlap, nx, nz;


		CVector3D otherPos = s_other->GetPos();

		//当たり判定の半径の合計を求める
		minDist = this->mCollisionRange + s_other->GetCollisionRange();

		// 各軸の距離を求めて、範囲外であればスルー
		if (abs(mPos.x - otherPos.x) > minDist) return false;
		if (abs(mPos.y - otherPos.y) > minDist) return false;
		if (abs(mPos.z - otherPos.z )  > minDist * 0.1f) return false; //z軸は判定小さく



		// x,z軸の距離を求める
		dx = mPos.x - otherPos.x;
		dz = mPos.z  - otherPos.z ;


		//√dx^2 dz^2 実際の距離を求める
		dist = sqrtf(dx * dx + dz * dz);

		//重なっていたら、押し戻す
		overlap = minDist - dist;

		//正規化して押し戻し方向を決める
		nx = dx / dist;
		nz = dz / dist;


		//それぞれを半分ずつ押し戻す
		mPos.x += nx * overlap * 0.5;
		mPos.z += nz * overlap * 0.5;
		otherPos.x += nx * overlap * 0.5;
		otherPos.z += nz * overlap * 0.5;

		//ノックバック距離を設定する
		mKnockbackdistance.x = nx * KNOCKBACK_RAITO;
		mKnockbackdistance.z = nz * KNOCKBACK_RAITO;


		//衝突先のタグ
		switch (s_other->GetTag())
		{
		case ETag::ENONE:
			break;
		case ETag::ESHUTOME:
			SceneManager::ChangeScene(SceneManager::ESCENE::CLEAR);

			break;
		case ETag::ETHROW:
			ChangeState(EState::ESTUN);

			// hpを減らす処理
			TakeDamage(1);

			mInvincibilityCnt = INVINCIBILITY_TIME;
			mIsStun = true;
			break;
		}


		return true;
	}

	
}


