#pragma once
#include"BaseScene.h"

class ClearScene :public BaseScene
{

public:

	ClearScene();//コンストラクタ
	~ClearScene();//デストラクタ

	void Update();//クリアシーン（でクリア画面のアニメーションとか）の更新関数
	void Draw();//クリアシーン（でクリア画面を描画したりとか）の描画関数
	void Init();
private:
	//ここにクリアシーンでいるものを書く(画像とかスコアとか)


protected:
	CImage* mpTitleImg;	// タイトルの画像
};
