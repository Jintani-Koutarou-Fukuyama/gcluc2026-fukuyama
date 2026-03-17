#include "StoryScene.h"
#include"SceneManager.h"


StoryScene::StoryScene()
{
	//ここにStoryScene()が生成されたときに呼び出したい処理を入れる

	//読み込みはタイトルでやっている
	// 再生（trueはループ）
	SOUND("story_bgm")->Play(true);
	printf("ストーリー中・・・\n");
	//画像読み込み
	mpStoryImg[0] = CImage::CreateImage("4KOMA_1.png");
	mpStoryImg[1] = CImage::CreateImage("4KOMA_2.png");
	mpStoryImg[2] = CImage::CreateImage("4KOMA_3.png");
	mpStoryImg[3] = CImage::CreateImage("4KOMA_4.png");

	// 4コマのサイズ
	for (int i = 0; i < 4; i++)
	{
		mpStoryImg[i]->SetSize(640, 360);
		mScale[i] = 1.0f;   // 最初は等倍
	}



	mPosIndex = 0;

	// 最初の位置
	mpStoryImg[0]->SetPos(0, 0);

	//矢印アイコン読み込み
	mpNextIcon = CImage::CreateImage("Enter矢印.png");
	mpNextIcon->SetSize(128, 64); // サイズ調整
	mpNextIcon->SetPos(1100, 650); // 右下

	mBlinkAlpha = 1.0f;   // 最初は不透明
	mBlinkSpeed = 0.02f;  // 点滅速度
	mBlinkUp = false;     // 最初は暗くなる方向

}

StoryScene::~StoryScene()
{
	//ここにStoryScene()が破棄されたときに呼び出したい処理を入れる

	for (int i = 0; i < 4; i++)
	{
		if (mpStoryImg[i])
		{
			mpStoryImg[i]->Release();
			delete mpStoryImg[i];
			mpStoryImg[i] = nullptr;
		}
		
	}
	if (mpNextIcon)
	{
		mpNextIcon->Release();
		delete mpNextIcon;
	}
	
	// BGM停止
	SOUND("story_bgm")->Stop();
	printf("シーンが変わりました\n");
}

//更新処理
void StoryScene::Update()
{
	//ここにStoryScene()があるときにずっと更新したい処理を入れる
	// エンターが押されたら次の位置へ
	if (PUSH(CInput::eButton10))
	{
		// まだ4コマ出ていないなら次のコマへ
		if (mPosIndex < 3)
		{
			mPosIndex++;

			// 新しいコマのポップアップ開始
			mScale[mPosIndex] = 0.8f;

			// 4つの位置
			switch (mPosIndex)
			{
			case 0: mpStoryImg[0]->SetPos(0, 0); break;
			case 1: mpStoryImg[1]->SetPos(0, 360); break;
			case 2: mpStoryImg[2]->SetPos(640, 0); break;
			case 3: mpStoryImg[3]->SetPos(640, 360); break;
			}
		}
		else
		{
			//4コマ全部出た後にエンターを押すと
			//シーンをチュートリアルに変更
			SceneManager::ChangeScene(SceneManager::TUTORIAL);
			return;
		}

	}

	// 点滅処理
	if (mBlinkUp)
	{
		mBlinkAlpha += mBlinkSpeed;
		if (mBlinkAlpha >= 1.0f)
		{
			mBlinkAlpha = 1.0f;
			mBlinkUp = false;
		}
	}
	else
	{
		mBlinkAlpha -= mBlinkSpeed;
		if (mBlinkAlpha <= 0.0f)
		{
			mBlinkAlpha = 0.0f;
			mBlinkUp = true;
		}
	}

	// α値をセット（r,g,b,a）
	mpNextIcon->SetColor(1.0f, 1.0f, 1.0f, mBlinkAlpha);

	// 新しいコマをポップアップさせる
		if (mScale[mPosIndex] < 1.0f)
		{
			mScale[mPosIndex] += 0.04f;   // 速度調整
			if (mScale[mPosIndex] > 1.0f)
				mScale[mPosIndex] = 1.0f;
		}

}


//描画処理
void StoryScene::Draw()
{
	//ここにStoryScene()があるときにずっと描画したいしたい処理を入れる
	for (int i = 0; i <= mPosIndex; i++)
	{
		// 拡大率を反映
		mpStoryImg[i]->SetSize(640 * mScale[i], 360 * mScale[i]);
		mpStoryImg[i]->Draw();
	}

	// 点滅アイコンを描画
	mpNextIcon->Draw();

}
void StoryScene::Init()
{
	
}
