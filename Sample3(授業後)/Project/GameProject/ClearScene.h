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
	void ArankScene();//クリアタイムが速かったら
	void BrankScene();//クリアタイムが普通だったら
	void CrankScene();//クリアタイムが遅かったら

private:
	//ここにクリアシーンでいるものを書く(画像とかスコアとか)
	bool RankTime= false;

protected:
	CImage* mpTitleImg;	// クリアシーンの画像
	CImage* mpNumberImg;//数字の画像
	CImage* mpRankImg; //評価の画像
	int mClearTime;
	void DrawNumber(int num, int x, int y);
	
};
