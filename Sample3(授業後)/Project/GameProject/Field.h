#pragma once
#include"Task.h"
// フィールドクラス
class Field:public Task
{
public:
	// コンストラクタ
	Field();
	// デストラクタ
	~Field();

	// 更新
	void Update()override;
	// 描画
	void PreRender()override;

	static int sFieldWidth;//フィールドのサイズを取得

protected:
	CImage* mpFieldImg[3];	// フィールドの画像
	

};