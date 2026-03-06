#pragma once
#include "CRectangle.h"
#include "CTexture.h"
#include "CCharacter.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CPlayer.h"
#include "CFont.h"
#include "CMiss.h"
#include "CCharacterManager.h"
#include "CGame.h"
#include "CPlayer2.h"
#include "CEnemy2.h"
#include "CSound.h"


class CApplication
{
public:
	enum class EState
	{
		ESTART,	//ゲーム開始
		EPLAY,	//ゲーム中
		ECLEAR,	//ゲームクリア
		EOVER,	//ゲームオーバー
	};

public:
	static CCharacterManager* CharacterManager();
	static CTexture* Texture();

	//最初に一度だけ実行するプログラム
	void Start();
	//繰り返し実行するプログラム
	void Update();
private:
	CSound mSoundBgm;	//BGM
	CSound mSoundOver;
	CGame* mpGame;
	static CCharacterManager mCharacterManager;
	EState mState;
	CInput mInput;
	CFont mFont;
	CPlayer* mpPlayer;
	static CTexture mTexture;
	CMiss* mpMiss;
	CEnemy* mpEnemy;
	CPlayer2* mpPlayer2;
	CEnemy2* mpEnemy2;
		
	
	
};