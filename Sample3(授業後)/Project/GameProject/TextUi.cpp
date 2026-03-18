#include "TextUi.h"

#define SIZE CVector2D(1280.0f, 300.0f) * 0.3f
#define CENTER_POS CVector2D(640.0f, 150.0f) * 0.3f	// 中心座標


#define TEX_EKEY "Enterキーを押す.png"

TextUi::TextUi(CVector2D s_pos)
	: Task((int)ETaskPrio::EUI)
	, mpEnterkeyImg(nullptr)
	, mIsDraw(false)
{
	// "Enterキーを押す"と書いてある画像を読み込む
	mpEnterkeyImg = CImage::CreateImage(TEX_EKEY);


	mpEnterkeyImg->SetCenter(CENTER_POS);
	mpEnterkeyImg->SetSize(SIZE);
	mpEnterkeyImg->SetPos(CVector2D(s_pos.x, s_pos.y + 50.0f));
}

TextUi::~TextUi()
{
	// Enterキー(ゲームを終了するキー)画像を削除
	if (mpEnterkeyImg != nullptr)
	{
		delete mpEnterkeyImg;
		mpEnterkeyImg = nullptr;
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
		mpEnterkeyImg->Draw();
	}
}

// 画像の描画、非描画の設定
void TextUi::SetIsDraw(bool s_isdraw)
{
	if (mIsDraw == s_isdraw) return;
	mIsDraw = s_isdraw;
}

