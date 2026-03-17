#include "StoryScene.h"
#include"SceneManager.h"


StoryScene::StoryScene()
{
	//ここにStoryScene()が生成されたときに呼び出したい処理を入れる

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
		m_scale[i] = 1.0f;   // 最初は等倍
	}



	m_posIndex = 0;

	// 最初の位置
	mpStoryImg[0]->SetPos(0, 0);

	//矢印アイコン読み込み
	m_nextIcon = CImage::CreateImage("Enter矢印.png");
	m_nextIcon->SetSize(128, 64); // サイズ調整
	m_nextIcon->SetPos(1100, 650); // 右下

	m_blinkAlpha = 1.0f;   // 最初は不透明
	m_blinkSpeed = 0.02f;  // 点滅速度
	m_blinkUp = false;     // 最初は暗くなる方向

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
	if (m_nextIcon)
	{
		m_nextIcon->Release();
		delete m_nextIcon;
	}

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
		if (m_posIndex < 3)
		{
			m_posIndex++;

			// 新しいコマのポップアップ開始
			m_scale[m_posIndex] = 0.8f;

			// 4つの位置
			switch (m_posIndex)
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
			//シーンをゲームに変更
			SceneManager::ChangeScene(SceneManager::GAME);
			return;
		}

	}

	// 点滅処理
	if (m_blinkUp)
	{
		m_blinkAlpha += m_blinkSpeed;
		if (m_blinkAlpha >= 1.0f)
		{
			m_blinkAlpha = 1.0f;
			m_blinkUp = false;
		}
	}
	else
	{
		m_blinkAlpha -= m_blinkSpeed;
		if (m_blinkAlpha <= 0.0f)
		{
			m_blinkAlpha = 0.0f;
			m_blinkUp = true;
		}
	}

	// α値をセット（r,g,b,a）
	m_nextIcon->SetColor(1.0f, 1.0f, 1.0f, m_blinkAlpha);

	// 新しいコマをポップアップさせる
		if (m_scale[m_posIndex] < 1.0f)
		{
			m_scale[m_posIndex] += 0.04f;   // 速度調整
			if (m_scale[m_posIndex] > 1.0f)
				m_scale[m_posIndex] = 1.0f;
		}

}


//描画処理
void StoryScene::Draw()
{
	//ここにStoryScene()があるときにずっと描画したいしたい処理を入れる
	for (int i = 0; i <= m_posIndex; i++)
	{
		// 拡大率を反映
		mpStoryImg[i]->SetSize(640 * m_scale[i], 360 * m_scale[i]);
		mpStoryImg[i]->Draw();
	}

	// 点滅アイコンを描画
	m_nextIcon->Draw();

}
void StoryScene::Init()
{
	
}
