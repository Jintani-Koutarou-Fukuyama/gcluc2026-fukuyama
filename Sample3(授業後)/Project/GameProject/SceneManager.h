#pragma once
#include"BaseScene.h"

class SceneManager {
public:
    enum ESCENE {
        TITLE,
        GAME,
        CLEAR,
        OVER
    };
    static void ChangeScene(ESCENE s_scene);     //シーンを引数によって変える関数
    static void Update();                     //現在のシーンの更新関数
    static void Render();                     //現在のシーンの描画関数
private:
    static BaseScene* mpScene;               //現在のシーン
};
