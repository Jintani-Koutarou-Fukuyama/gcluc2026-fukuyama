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
	int mPosIndex;  // 現在の位置インデックス（0〜3）
	CImage* mpNextIcon;   // 右下の点滅アイコン
	float mBlinkAlpha;   // 透明度
	float mBlinkSpeed;   // 点滅速度
	bool mBlinkUp;       // α値が上昇中か下降中か
	float mScale[4];
	CImage* mpMaeokiImg;   // 最初に出す画像
	bool mMaeokiDone;     // 導入画像が終わったかどうか
	float mMaeokiY;        // 導入画像の現在のY座標
	float mMaeokiSpeed;    // スクロール速度
	bool mMaeokiScrollEnd; // スクロールが終わったかどうか

};
