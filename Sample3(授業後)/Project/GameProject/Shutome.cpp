#include "Shutome.h"
#include "Player.h"
#include "TaskManager.h"


#define CHIP_SIZE 700		// 1コマのサイズ
#define CENTER_POS CVector2D(173.0f, 350.0f)	// 中心座標


#define TEX_SHUTOME "姑.png"



// 姑のアニメーションデータの前宣言
TexAnimData Shutome::ANIM_DATA[(int)EAnimeType::ENUM] =
{
	//待機アニメーション
	{
		new TexAnim[1]
	    {
		    {0, 6},
        },
		1
    }
};

// コンストラクタ
Shutome::Shutome(const CVector3D& s_pos, const float& s_collisionRange)
	: EnemyBase(s_pos, s_collisionRange)
	, mpImage(nullptr)
	, mpEnterkey(nullptr)
{
	mHp = 100; 
	mTag = ObjectBase::ETag::ESHUTOME;


	// 姑の画像を読み込み
	mpImage = CImage::CreateImage
	(
		TEX_SHUTOME,	// 画像ファイルのパス
		ANIM_DATA,		// アニメーションのデータ
		CHIP_SIZE, CHIP_SIZE	// 1コマの幅と高さ
	);
	mpImage->ChangeAnimation((int)EAnimeType::EIDLE);
	mpImage->SetCenter(CENTER_POS);

	mpImage->SetSize(CVector2D(350.0f, 390.0f));

	mpEnterkey = new TextUi(CVector2D(SCREEN_WIDTH * 0.85f, 150.0f));

}

Shutome::~Shutome()
{
	// 画像を削除
	if (mpImage != nullptr)
	{
		delete mpImage;
		mpImage = nullptr;
	}
	mpEnterkey->Kill();
	mpEnterkey = nullptr;
}

void Shutome::StateIdle()
{
	mpImage->ChangeAnimation((int)EAnimeType::EIDLE);
}


void Shutome::Update()
{

	StateIdle();

	// イメージに座標を設定して、アニメーションを更新
	mpImage->SetPos(CalcScreenPos());
	mpImage->UpdateAnimation();
	
}

void Shutome::Render()
{
	mpImage->Draw();
}

bool Shutome::Collision(ObjectBase* s_other)
{
	return false;
}


void Shutome::SetIsDrawEnterkey(bool s_isdraw)
{
	// 画像を表示するかどうかを設定する
	mpEnterkey->SetIsDraw(s_isdraw);
}

