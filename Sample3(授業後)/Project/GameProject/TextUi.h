#pragma once
#include "Task.h"

class TextUi : public Task
{
public:
	// コンストラクタ
	TextUi(CVector2D s_pos);
	// デストラクタ
	~TextUi();


	// 更新
	void Update()override;
	// 描画
	void PreRender()override;
	void Render() override;
	// 画像の描画、非描画の設定
	void SetIsDraw(bool s_isdraw);
private:

	CImage* mpEkeyImg;
	bool mIsDraw; // trueであれば画像を描画する
};

