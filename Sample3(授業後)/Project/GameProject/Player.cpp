#include "Player.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "DropObstacle.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Hubby.h"
#include "HealItem.h"
#include "Shutome.h"
#include "TextUi.h"


#define CHIP_SIZE 700.0f		// 1コマのサイズ
#define CENTER_POS CVector2D(170.0f, 322.0f)	// 中心座標
#define MOVE_SPEED_X 5.0f	// 横方向の移動速度
#define MOVE_SPEED_Z 3.0f	// 奥方向の移動速度
#define JUMP_SPEED 20.0f	// ジャンプ速度
#define GRAVITY -1.0f		// 重力
#define ATTACK_INDEX 2		// 攻撃が発生するアニメーションの番号
#define ATTACK_RANGE CVector3D(300.0f, 10.0f, 50.0f)	// 攻撃範囲
#define KNOCKBACK_RAITO 1.2f  //ノックバック距離、ノックバックの距離を決める
#define INVINCIBILITY_TIME 10 //無敵時間

<<<<<<< Updated upstream
#define TEX_PLAYER "嫁絵.png"
=======
#define GAMEOVER_RANGE 50.0f

#define TEX_PLAYER "嫁 .png"
>>>>>>> Stashed changes

Player* Player::mspInstance = nullptr;
// プレイヤーのアニメーションデータの前宣言
TexAnimData Player::ANIM_DATA[(int)EAnimType::ENUM] =
{
	// 待機アニメーション
	{
		new TexAnim[1]
		{
			{0, 6},
		},
		1
	},
	// 移動アニメーション
	{
		new TexAnim[2]
		{
			{1, 15}, {2, 15},
		},
		2
	},
	// 死亡アニメーション
	{
		new TexAnim[3]
		{
			{12, 12},
			{13, 12},
			{14, 12},
		},
		
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
			{3, 20},   //次の画像までの待機フレーム(2番目の値)でスタンの長さが変わる
		},
		1
	},
	// ジャンプアニメーション
	{
		new TexAnim[1]
		{
			{4, 20},   
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
	mTag = ETag::PLAYER;

	// プレイヤーの画像を読み込み
	mpImage = CImage::CreateImage
	(
		TEX_PLAYER,	// 画像ファイルのパス
		ANIM_DATA,		// アニメーションのデータ
		CHIP_SIZE, CHIP_SIZE	// 1コマの幅と高さ
	);
	mpImage->ChangeAnimation((int)EAnimType::EIDLE);
	mpImage->SetCenter(CENTER_POS);

	mpImage->SetSize(CVector2D(350.0f, 340.0f));
	mspInstance = this;
}

// デストラクタ
Player::~Player()
{
	// 画像を削除
	if (mpImage != nullptr)
	{
		delete mpImage;
		mpImage = nullptr;
	}
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
	/* [X] キーで攻撃状態へ移行
	else if (PUSH(CInput::eButton2))
	{
		ChangeState(EState::EATTACK);
	}
	*/

	
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

			mpImage->ChangeAnimation((int)EAnimType::EJUNP);
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
	mpImage->ChangeAnimation((int)EAnimType::EJUNP);
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
	if (!isDead) {
		isDead = true;  // 一度だけ true にする
		//SceneManager::ChangeScene(SceneManager::ESCENE::OVER);
		SceneManager::Instance()->isover = true;
		return;
	}


}
	

// スタン時の更新処理
void Player::StateStun()
{
	// ステップごとに処理を切り替え
	switch (mStateStep)
	{
		// ステップ0：スタンアニメーションに切り替え
	case 0:

		mpImage->ChangeAnimation((int)EAnimType::ESTUN, false);

		// 無敵時間をセット
		mInvincibilityCnt = INVINCIBILITY_TIME;
		mIsStun = true;

		mStateStep++;

		break;

		// ステップ2：アニメーション終了待ち
	case 1:
		if (mIsStun)
		{
			// ノックバック距離を位置に加算する
			mPos += mKnockbackdistance;
		}
		

		// スタンアニメーションが終了したら、待機状態へ移行
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
		mPos.z = -120.0f;
	}
	


	//画面の左（画像の一番右）に行くと
	if (mPos.x >= 9100.0f)
	{
		//それ以上いけないようにする
		mPos.x = 9100.0f;//画像の大きさが変わるたびに変更
	}
	// イメージに座標を設定して、アニメーションを更新
	mpImage->SetPos(CalcScreenPos());
	mpImage->UpdateAnimation();

	//DebugPrint::Print("プレイヤー位置：%.2f, %.2f, %.2f", mPos.x, mPos.y, mPos.z);

	Camera::Instance()->SetTargetPos(mPos);

	if (mInvincibilityCnt >= 1)
	{
		mInvincibilityCnt--;
	}
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

	Shutome* shutome;


	//衝突先のタグ
	switch (s_other->GetTag())
	{
	case ETag::ENONE:
		break;
	case ETag::ESHUTOME:
		// 姑に使づいたときの処理
		shutome = (Shutome*)s_other;
		float minDist = this->mCollisionRange + shutome->GetCollisionRange();

		// 各軸の距離を求めて、範囲外であればスルー
		if (abs(mPos.x - shutome->GetPos().x) < minDist + GAMEOVER_RANGE)
		{
			if (abs(mPos.y - shutome->GetPos().y) < minDist + GAMEOVER_RANGE)
			{
				if (abs(mPos.z - shutome->GetPos().z) < (minDist + GAMEOVER_RANGE) * 0.4f) //z軸は判定小さく
				{
					// "Eキーを押す"という文字を描画する
					shutome->SetIsDrawEkey(true);

					// Eキーでゲーム終了
					if (HOLD(CInput::eButton11))
					{
						if (!isClear)
						{
							isClear = true;//一度だけtrueにする
							//SceneManager::ChangeScene(SceneManager::ESCENE::CLEAR);

							SceneManager::Instance()->isclear = true;

						}
					}
					break;
				}
				else
				{
					// "Eキーを押す"という文字を描画しない
					shutome->SetIsDrawEkey(false);

				}

			}
			else
			{
				// "Eキーを押す"という文字を描画しない
				shutome->SetIsDrawEkey(false);

			}
		}
		else
		{
			// "Eキーを押す"という文字を描画しない
			shutome->SetIsDrawEkey(false);
		}
		
	}
	
	
	// スタン状態ならスルー
	if (mIsStun == false) 
	{

		// TODO: Z軸の当たり判定が大きいかもしれない。直方体型にする


		float dx, dz, dist, minDist, overlap, nx, nz;


		CVector3D otherPos = s_other->GetPos();

		//当たり判定の半径の合計を求める
		minDist = this->mCollisionRange + s_other->GetCollisionRange();

		// 各軸の距離を求めて、範囲外であればスルー
		if (abs(mPos.x - otherPos.x) > minDist) return false;
		if (s_other->GetTag() != ETag::ETHROW)   // ← 皿以外ならY判定する
		{
			float heightRange = minDist * 1.2f;
			if (abs(mPos.y - otherPos.y) > heightRange) return false;
		}
		if (abs(mPos.z - otherPos.z )  > minDist * 0.2f) return false; //z軸は判定小さく



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
		mPos.z += nz * overlap * 0.5 * 0.2; //z軸は押し戻し小さく(判定に合わせる)
		otherPos.x += nx * overlap * 0.5;
		otherPos.z += nz * overlap * 0.5 * 0.2; //z軸は押し戻し小さく(判定に合わせる)

		//ノックバック距離を設定する
		mKnockbackdistance.x = nx * KNOCKBACK_RAITO;
		mKnockbackdistance.z = nz * KNOCKBACK_RAITO;


		//衝突先のタグ
		switch (s_other->GetTag())
		{
		case ETag::ENONE:
			break;
		case ETag::ESHUTOME:

			if (HOLD(CInput::eButton11))
			{
				if (!isClear)
				{
					isClear = true;//一度だけtrueにする
					//SceneManager::ChangeScene(SceneManager::ESCENE::CLEAR);

					SceneManager::Instance()->isclear = true;

				}
			}
			
			break;
		case ETag::ETHROW:
			ChangeState(EState::ESTUN);

			// hpを減らす処理
			TakeDamage(1);


			break;
		case ETag::EDROPOBSTACLE:
		{
			ChangeState(EState::ESTUN);


			// hpを減らす処理
			TakeDamage(1);

			// 落ちてくる障害物をDeath状態にする
			DropObstacle* obj = (DropObstacle*)s_other;
			obj->ChangeState(DropObstacle::EState::EDEATH);
			break;
		}

		}

		return true;
	}

	
}


