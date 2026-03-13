#include "Field.h"
#include"Camera.h"
#include "ShutomeCutIn.h"
#include "Player.h"

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

	int area = GetArea();

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

int Field::GetArea()
{
	if (Player::GetInstance() == nullptr) return 0;

	float playerX = Player::GetInstance()->GetPos().x;

	int w = sFieldWidth / 3;

	int area = playerX / w;

	if (area < 0) area = 0;
	if (area > 2) area = 2;

	return area;
}