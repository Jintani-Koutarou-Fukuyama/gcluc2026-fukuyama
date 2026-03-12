#pragma once
#include"BaseScene.h"


class GameScene :public BaseScene
{

public:

	GameScene();
	~GameScene();

	void Update();//ゲームシーン（でゲームのアニメーションとか）の更新関数
	void Draw();//ゲームシーン（でゲームを描画したりとか）の描画関数
	void Init();//タスクマネージャーに登場された後に呼ぶもの

private:
	//ここにゲームシーンでいるものを書く(画像とかスコアとか)

};
