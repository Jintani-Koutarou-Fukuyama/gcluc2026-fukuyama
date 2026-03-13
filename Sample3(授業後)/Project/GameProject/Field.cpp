#include "Field.h"
#include"Camera.h"
#include "ShutomeCutIn.h"

#define TEX_FIELD "22仮.png"

int Field::sFieldWidth = 0;


// コンストラクタ
Field::Field()
	: Task((int)ETaskPrio::EFIELD)
	
{
	// フィールド画像を読み込み

	mpFieldImg[0] = CImage::CreateImage("22仮.png");
	mpFieldImg[1] = CImage::CreateImage("22仮.png");
	mpFieldImg[2] = CImage::CreateImage("22仮.png");


	// 1枚の幅を取得
	int w = mpFieldImg[0]->GetSize().x;

	// フィールド全体の幅
	sFieldWidth = w * 3;


}

// デストラクタ
Field::~Field()
{
	for (int i = 0; i < 3; i++) {
		if (mpFieldImg[i] != nullptr) {
			delete mpFieldImg[i];
			mpFieldImg[i] = nullptr;
		}
	}

}

// 更新
void Field::Update()
{
	static int prevArea = -1;

	int w = mpFieldImg[0]->GetSize().x;

	int area = Camera::GetOffset().x / w;

	if (area != prevArea)
	{
		prevArea = area;

		if (area > 0)
		{
			new ShutomeCutIn(area);
		}
	}
}

// 描画
void Field::PreRender()
{
	CVector2D cam = Camera::GetOffset();

	for (int i = 0; i < 3; i++) {
		CVector2D pos = cam;
		pos.x += mpFieldImg[0]->GetSize().x * i;  // 横に並べる

		mpFieldImg[i]->SetPos(pos);
		mpFieldImg[i]->Draw();
	}

}
