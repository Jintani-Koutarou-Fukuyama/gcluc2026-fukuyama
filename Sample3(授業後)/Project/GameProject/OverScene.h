#pragma once
#include"BaseScene.h"


class OverScene :public BaseScene
{

public:

	OverScene();
	~OverScene();

	void Update();//ゲームオーバーシーン（でゲームオーバーのアニメーションとか）の更新関数
	void Draw();//ゲームオーバーシーン（でゲームオーバーを描画したりとか）の描画関数

private:
	//ここにゲームオーバーシーンでいるものを書く(画像とかスコアとか)

};
