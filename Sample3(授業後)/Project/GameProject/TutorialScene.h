#pragma once
#include"BaseScene.h"


class TutorialScene :public BaseScene
{

public:

	TutorialScene();//コンストラクタ
	~TutorialScene();//デストラクタ

	void Update();//チュートリアルシーン（でタイトル画面のアニメーションとか）の更新関数
	void Draw();//チュートリアルシーン（でタイトル画面を描画したりとか）の描画関数
	void Init();//タスクマネージャーに登場された後に呼ぶもの
private:
	//ここにチュートリアルシーンでいるものを書く(画像とか)
	CImage* mpTutorialImg[5]; //チュートリアル画像5枚
	int mPage;                //現在のページ

	CImage* mpNextIcon;   // 矢印アイコン
	float mBlinkAlpha;    // 透明度
	float mBlinkSpeed;    // 点滅速度
	bool mBlinkUp;        // 点滅方向
//protected:
//	CImage* mpTutorialImg;	// チュートリアルの画像

};