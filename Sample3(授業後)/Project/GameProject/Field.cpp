#include "Field.h"

#define TEX_SHADOW "22仮.png"

// コンストラクタ
Field::Field()
	: Task((int)ETaskPrio::EFIELD)
	,mpFieldImg(nullptr)
{
	// フィールド画像を読み込み
	mpFieldImg = CImage::CreateImage(TEX_SHADOW);
}

// デストラクタ
Field::~Field()
{
	// フィールドの画像を削除
	if (mpFieldImg != nullptr)
	{
		delete mpFieldImg;
		mpFieldImg = nullptr;
	}
}

// 更新
void Field::Update()
{
}

// 描画
void Field::PreRender()
{
	// フィールドを描画
	mpFieldImg->Draw();
}
