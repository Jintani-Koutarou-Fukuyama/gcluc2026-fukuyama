#include "StoryScene.h"

StoryScene::StoryScene()
{
	//ここにStoryScene()が生成されたときに呼び出したい処理を入れる

	printf("ストーリー中・・・\n");

}

StoryScene::~StoryScene()
{
	//ここにStoryScene()が破棄されたときに呼び出したい処理を入れる
	printf("シーンが変わりました\n");
}

//更新処理
void StoryScene::Update()
{
	//ここにStoryScene()があるときにずっと更新したい処理を入れる
	
}


//描画処理
void StoryScene::Draw()
{
	//ここにStoryScene()があるときにずっと描画したいしたい処理を入れる

}