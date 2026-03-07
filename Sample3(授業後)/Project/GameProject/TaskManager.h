#pragma once

class Task;

//タスクを管理するクラス
class TaskManager
{
public:
	//TaskManagerのインスタンスを取得
	static TaskManager* Instance();
	//TaskManagerのいインスタンスを破棄
	static void ClearInstance();

	//タスクリストにタスクを追加
	void Add(Task* s_task, bool s_sort = false);
	//タスクリストからタスクを取り除く
	void Remove(Task* s_task, bool s_sort = false);
	//すべてのタスクを削除
	void DeleteAll();
	//削除フラグが立っているタスクを削除
	void DeleteKilledTasks();

	//タスクリストに登録されているタスクをすべて更新
	void Update();
	//タスクリストに登録されているタスクをすべて描画
	void Render();

private:
	//コンストラクタ
	TaskManager();
	TaskManager(const TaskManager&) = delete;
	TaskManager& operator=(const TaskManager&) = delete;
	//デストラクタ
	~TaskManager();

	//TaskManagerのインスタンスのポインタ
	static TaskManager* msInstance;

	//生成済みのタスクのリスト
	std::list<Task*> mTaskuList;
	//生成済みのオブジェクトのリスト
	std::list<Task*>mObjectList;
};