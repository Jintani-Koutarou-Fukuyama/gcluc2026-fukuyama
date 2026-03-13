#pragma once
#include"BaseScene.h"

class StoryScene :public BaseScene
{

public:

	StoryScene();//コンストラクタ
	~StoryScene();//デストラクタ

	void Update();//ストーリシーン（でストーリー画面のアニメーションとか）の更新関数
	void Draw();//ストーリーシーン（でストーリー画面を描画したりとか）の描画関数
	void Init();//タスクマネージャーに登場された後に呼ぶもの
private:
	//ここにストーリーシーンでいるものを書く(画像とか)

};
