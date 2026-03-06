#pragma once
class Task;
//前宣言
//Taskがあるということだけを宣言する
//cppでincludeする
//このコードで Task m_taskをするとエラーになる
//ポインタや参照しているだけならば前宣言でいい
//ビルド処理が軽くなる

//タスクを管理するクラス
class TaskManager
{
public:
	//TaskManagerのインスタンスを取得
	static TaskManager* Instance();
	//TaskManagerのインスタンスを破棄
	static void ClearInstance();

	//シングルトン

	//タスクリストにタスクを追加
	void Add(Task* task, bool sort = false);
	//タスクリストからタスクを取り除く
	void Remove(Task* taskm, bool sort = false);


	//全てのタスクを削除
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
	//コピーコンストラクタを破棄する(これで厳密なシングルトンになる)
	TaskManager(const TaskManager&) = delete;
	TaskManager& operator=(const TaskManager&) = delete;

	//デストラクタ
	~TaskManager();

	//privateにコンストラクタを書くことによって、外部から生成することができない


	static TaskManager* ms_instance;
	
	//　生成済みのタスクのリスト
	std::list<Task*> m_taskList;
	// 生成済みのオブジェクトのリスト
	std::list<Task*> m_objectList;
};