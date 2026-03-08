#include "Field.h"
#include"Camera.h"

#define TEX_SHADOW "22仮.png"

int Field::sFieldWidth = 0;


// コンストラクタ
Field::Field()
	: Task((int)ETaskPrio::EFIELD)
	,mpFieldImg(nullptr)
{
	// フィールド画像を読み込み
	mpFieldImg = CImage::CreateImage(TEX_SHADOW);
	sFieldWidth = mpFieldImg->GetSize().x;//フィールドのサイズを取得

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
	mpFieldImg->SetPos(Camera::GetOffset());

	// フィールドを描画
	mpFieldImg->Draw();
}
