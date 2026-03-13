#pragma once
#include "Task.h"

class Ui :public Task
{
public:
	//コンストラクタ
	Ui();
	//デストラクタ
	~Ui();

	// 更新
	void Update()override;
	// 描画
	void PreRender()override;
	void Render() override;

	int UiKaisi = false;

	int GetTimeSec() const;

protected:
	CImage* mpHpImg;	// HPの画像
	CImage* mpUiFrame; //HPフレームの画像
	CImage* mpUiFrameTimer;//タイマーフレーム
	int mpHp;
	int mTimer;
	CImage* mpNumberImg; //数字の画像
	void DrawNumber(int num, int x, int y);

};