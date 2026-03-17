#pragma once
#include"BaseScene.h"

struct ObstacleData
{
	float x;
	float z;
};

class GameScene :public BaseScene
{

public:

	GameScene();
	~GameScene();

	void Update();//ゲームシーン（でゲームのアニメーションとか）の更新関数
	void Draw();//ゲームシーン（でゲームを描画したりとか）の描画関数
	void Init();//タスクマネージャーに登場された後に呼ぶもの


	// 皿の設定(間隔を設定する)
	void SetPlateGimmick(float s_interval);
	// 皿を生成する
	void PopPlate();
private:
	//ここにゲームシーンでいるものを書く(画像とかスコアとか)
	int mDifficultyLevel = 0;  //難易度フラグ 0=LEVEL1, 1=LEVEL2, 2=LEVEL3
	std::vector<ObstacleData> mObstacleQueue;
	int mObstacleCreatePerFrame = 5; // 1フレームに5個ずつ生成


	float mElapsedTime;	// 経過時間計測用
	int mSpawnCnt;    // スポーンカウント
	int mInterval;    //生成時間

};
