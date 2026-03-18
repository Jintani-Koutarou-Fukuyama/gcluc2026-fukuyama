#include "TextUi.h"

#define SIZE CVector2D(1280.0f, 300.0f) * 0.3f
#define CENTER_POS CVector2D(640.0f, 150.0f) * 0.3f	// 中心座標


#define TEX_EKEY "Eキーを押す.png"

TextUi::TextUi(CVector2D s_pos)
	: Task((int)ETaskPrio::EUI)
	, mpEkeyImg(nullptr)
	, mIsDraw(false)
{
	// "Eキーを押す"と書いてある画像を読み込む
	mpEkeyImg = CImage::CreateImage(TEX_EKEY);


	mpEkeyImg->SetCenter(CENTER_POS);
	mpEkeyImg->SetSize(SIZE);
	mpEkeyImg->SetPos(CVector2D(s_pos.x, s_pos.y + 50.0f));
}

TextUi::~TextUi()
{
	// Eキー(ゲームを終了するキー)画像を削除
	if (mpEkeyImg != nullptr)
	{
		delete mpEkeyImg;
		mpEkeyImg = nullptr;
	}
}

void TextUi::Update()
{
	;
}

void TextUi::PreRender()
{
	;
}

void TextUi::Render()
{
	if (mIsDraw)
	{
		mpEkeyImg->Draw();
	}
}

// 画像の描画、非描画の設定
void TextUi::SetIsDraw(bool s_isdraw)
{
	if (mIsDraw == s_isdraw) return;
	mIsDraw = s_isdraw;
}

