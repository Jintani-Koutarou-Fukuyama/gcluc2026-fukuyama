#include"SceneManager.h"
#include"TitleScene.h"
#include"ClearScene.h"
#include"OverScene.h"
#include"GameScene.h"
#include"StoryScene.h"
#include"TaskManager.h"
#include"Camera.h"
BaseScene* SceneManager::mpScene = nullptr;
SceneManager* SceneManager::msInstance = nullptr;


SceneManager::SceneManager()
{
    
} 

SceneManager* SceneManager::Instance()
{
    if (msInstance == nullptr)
    {
        msInstance = new SceneManager();
    }
    return msInstance;
}

void SceneManager::ChangeScene(ESCENE s_scene)//シーンが変わるときに呼び出す

{
    TaskManager::Instance()->DeleteAll();
   
    //mpSceneにシーンが入っていたら破棄する
    if (mpScene != NULL)
    {
        delete mpScene;
    }

    switch (s_scene) {          //引数のシーン
    case ESCENE::TITLE:
        mpScene = new TitleScene(); //タイトルシーンを現在のシーンにする
        break;
    case ESCENE::GAME:
        mpScene = new GameScene(); //ゲームシーンを現在のシーンにする
       break;
    case ESCENE::CLEAR:
        mpScene = new ClearScene(); //リザルトシーンを現在のシーンにする
        break;
    case ESCENE::OVER:
        mpScene = new OverScene(); //ゲームオーバーシーンを現在のシーンにする
        break;
    case ESCENE::STORY:
        mpScene = new StoryScene(); //ストーリーシーンを現在のシーンにする
        break;
    default:
        break;
    }
    mpScene->Init();

}


void SceneManager::Update() {
    if (mpScene) mpScene->Update();//現在のシーンの更新関数
    Camera::Instance()->Update();
}

void SceneManager::Render() {
    if (mpScene) mpScene->Draw();//現在のシーンの描画関数
}
