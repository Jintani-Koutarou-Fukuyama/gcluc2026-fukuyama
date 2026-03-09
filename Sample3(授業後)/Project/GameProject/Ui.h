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

protected:
	CImage* mpHpImg;	// HPの画像
	int mpHp;

};