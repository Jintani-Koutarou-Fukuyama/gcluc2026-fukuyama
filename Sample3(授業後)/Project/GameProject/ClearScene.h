#pragma once
#include"BaseScene.h"

class ClearScene :public BaseScene
{

public:

	void Update();//クリアシーン（でクリア画面のアニメーションとか）の更新関数
	void Draw();//タイトルシーン（でクリア画面を描画したりとか）の描画関数

private:
	//ここにクリアシーンでいるものを書く(画像とかスコアとか)

};
