#include "Shutome.h"

#define CHIP_SIZE 384		// 1コマのサイズ
#define CENTER_POS CVector2D(192.0f, 328.0f)	// 中心座標


#define TEX_SHUTOME "player.png"

#define COLLISION_RANGE 20.0f // 姑の当たり判定の大きさ


// 姑のアニメーションデータの前宣言
TexAnimData Shutome::ANIM_DATA[(int)EAnimeType::ENUM] =
{
	//待機アニメーション
	{
		new TexAnim[6]
	    {
		    {0, 6}, {1, 6}, {2, 6},
	        {3, 6}, {4, 6}, {5, 6},
        },
    }
};

// コンストラクタ
Shutome::Shutome(const CVector3D& s_pos, const float& s_collisionRange)
	: EnemyBase(s_pos, s_collisionRange)
	, mpImage(nullptr)
{
	mHp = 100; 

	// 姑の画像を読み込み
	mpImage = CImage::CreateImage
	(
		TEX_SHUTOME,	// 画像ファイルのパス
		ANIM_DATA,		// アニメーションのデータ
		CHIP_SIZE, CHIP_SIZE	// 1コマの幅と高さ
	);
	mpImage->ChangeAnimation((int)EAnimeType::EIDLE);
	mpImage->SetCenter(CENTER_POS);

}

Shutome::~Shutome()
{
	delete mpImage;
}

void Shutome::Update()
{
}

void Shutome::Render()
{
}
