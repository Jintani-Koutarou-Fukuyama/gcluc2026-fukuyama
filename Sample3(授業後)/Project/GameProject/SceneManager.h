#pragma once
#include"BaseScene.h"
#include"Task.h"
class SceneManager
{
public:
    enum ESCENE {
        TITLE,
        GAME,
        CLEAR,
        OVER,
        STORY
    };

    SceneManager();
    static void ChangeScene(ESCENE s_scene);     //シーンを引数によって変える関数
    static void Update();                     //現在のシーンの更新関数
    static void Render(); //現在のシーンの描画関数
   
    
    bool isover = false;//ゲームオーバーフラグ
    bool isclear = false;//クリアフラグ
    bool requestChange = false;//フラグが立ったかのフラグ
    int clearTime = 0;//秒



    static SceneManager* Instance();
private:
    static BaseScene* mpScene;               //現在のシーン
    static SceneManager* msInstance;


};
