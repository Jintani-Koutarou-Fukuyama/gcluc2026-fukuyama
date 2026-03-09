#pragma once
#include"BaseScene.h"


class TitleScene :public BaseScene
{

public:

	TitleScene();//コンストラクタ
	 ~TitleScene();//デストラクタ

	void Update();//タイトルシーン（でタイトル画面のアニメーションとか）の更新関数
	void Draw();//タイトルシーン（でタイトル画面を描画したりとか）の描画関数
	
private:
	//ここにタイトルシーンでいるものを書く(画像とか)

protected:
	CImage* mpTitleImg;	// タイトルの画像

};