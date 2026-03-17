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
	CImage* mpStoryImg[4]; // 表示する画像  
	int m_posIndex;  // 現在の位置インデックス（0〜3）
	CImage* m_nextIcon;   // 右下の点滅アイコン
	float m_blinkAlpha;   // 透明度
	float m_blinkSpeed;   // 点滅速度
	bool m_blinkUp;       // α値が上昇中か下降中か
	float m_scale[4];
};
