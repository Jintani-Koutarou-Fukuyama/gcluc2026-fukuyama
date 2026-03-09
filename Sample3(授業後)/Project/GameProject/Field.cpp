#include "Field.h"
#include"Camera.h"

#define TEX_FIELD "22仮.png"

int Field::sFieldWidth = 0;


// コンストラクタ
Field::Field()
	: Task((int)ETaskPrio::EFIELD)
	,mpFieldImg(nullptr)
{
	// フィールド画像を読み込み
<<<<<<<<< Temporary merge branch 1
	mpFieldImg = CImage::CreateImage(TEX_FIELD);
=========
	
>>>>>>>>> Temporary merge branch 2
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
