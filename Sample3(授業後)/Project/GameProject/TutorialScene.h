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

protected:
	CImage* mpTutorialImg;	// チュートリアルの画像

};