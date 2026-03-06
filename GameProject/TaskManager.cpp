#include "TaskManager.h"
#include "Task.h"
#include "ObjectBase.h"

//静的なメンバ変数の定義
TaskManager* TaskManager::ms_instance = nullptr;

//コンストラクタ
TaskManager::TaskManager()
{

}
//デストラクタ
TaskManager::~TaskManager()
{
	//全てのタスクを削除
	DeleteAll();
}

//TaskManagerのインスタンスを取得
TaskManager* TaskManager::Instance()
{
	//インスタンスが生成されていなければ、
	//インスタンス生成後に返す
	if (ms_instance == nullptr)
	{
		ms_instance = new TaskManager();
	}
	return ms_instance;

}

//TaskManagerのインスタンスを破棄
void TaskManager::ClearInstance()
{
	if (ms_instance != nullptr)
	{
		delete ms_instance;
		ms_instance = nullptr;
	}
}

//タスクリストにタスクを追加
void TaskManager::Add(Task* task, bool sort)
{
	if (!sort)
	{
		//追加されるタスクがオブジェクトであれば、
		// オブジェクトリストにも登録
		if (task->m_prio == (int)ETaskPrio::Object)
		{
			m_objectList.push_back(task);
		}
	}
	//すべてのタスクを調べて、優先度順に追加する
	auto itr = m_taskList.begin(); //autoになっているのはデータ型が長いため
	                               //またリストのデータの型が変わってもエラーが起きないようにしている
	
	while (itr != m_taskList.end())
	{
		Task* curr = *itr;
		//追加するタスクの優先度の数値が小さい場合は、
		//その位置にタスクを追加する
		if (task->m_prio < curr->m_prio)
		{
			m_taskList.insert(itr, task);
			return;
		}
		//追加するタスクと現在比べているタスクの優先度が同じ場合は、
		//m_sortOrderの順番でリストに追加する
		else if (task->m_prio == curr->m_prio)
		{
			if (task->m_sortOrder < curr->m_sortOrder)
			{
				m_taskList.insert(itr, task);
				return;
			}
		}

		++itr;    //次のタスクへ1個進める

	}
	//リストの間に追加する場所が見つからなかったので、
	//リストの一番最後に追加
	m_taskList.push_back(task);
}

//タスクリストからタスクを取り除く
void TaskManager::Remove(Task* task, bool sort)
{
	//並び変え時でなければ、
	if (!sort)
	{
		//取り除くタスクがオブジェクトならば、オブジェクトリストからも取り除く
		if (task->m_prio == (int)ETaskPrio::Object)
		{
			m_objectList.remove(task);
		}
	}

	//指定されたタスクをタスクリストから取り除く
	m_taskList.remove(task);
}

//すべてのタスクを削除
void TaskManager::DeleteAll()
{
	//タスクリストの先頭から順番に削除する
	m_objectList.clear();

	auto itr = m_taskList.begin();
	while (itr != m_taskList.end())
	{
		//削除するタスクのアドレスを一旦記憶し、
		//リストから取り除いた後に、タスクを削除する
		Task* del = *itr;
		itr = m_taskList.erase(itr);
		delete del;
	}

}

//削除フラグが立っているタスクを削除
void TaskManager::DeleteKilledTasks()
{
	//タスクリストの先頭から順番に削除する
	m_objectList.clear();

	auto itr = m_taskList.begin();
	while (itr != m_taskList.end())
	{
		//削除フラグが立っていたら、削除する
		Task* del = *itr;
		if (del->m_isKill)
		{
			itr = m_taskList.erase(itr);
			delete del;
		}
		//削除フラグが立っていなければ、次のタスクを調べる
		else
		{
			++itr;
		}
		
	}
}

//タスクリストに登録されているタスク全てを更新
void TaskManager::Update()
{
	//削除フラグが立っているタスクすべて削除
	DeleteKilledTasks();

	//リストの先頭から順番に更新処理を呼び出す
	for (Task* task : m_taskList)
	{
		//タスクが有効であれば、更新
		if (task->IsEnable())
		{
			task->Update();
		}
	}
}

//タスクリストに登録されているタスクすべてを描画
void TaskManager::Render()
{
	//オブジェクトリストの中身を奥行の座標が大きい順に並べる
	m_objectList.sort
	(
		[](const Task* task0, const Task* task1)
		{
			const ObjectBase* obj0 = dynamic_cast<const ObjectBase*>(task0);
			const ObjectBase* obj1 = dynamic_cast<const ObjectBase*>(task1);
			return obj0->GetPos().z < obj1->GetPos().z;
		}
	);

	//並び変えたオブジェクトの先頭から順に
	// SortOrderの値を設定することで、タスクリストの中のオブジェクトリストの順番にも反映
	//
	int sortOrder = 0;
	for (Task* obj : m_objectList)
	{
		obj->SetSortOrder(sortOrder);
		sortOrder++;
	}

	//通常の描画より先に呼び出す描画処理
	for (Task* task : m_taskList)
	{
		//タスクが有効かつ表示状態ならば、描画
		if (task->IsEnable() && task->IsShow())
		{
			task->PreRender();
		}
	}

	//通常の描画
	for (Task* task : m_taskList)
	{
		//タスクが有効かつ表示状態ならば、描画
		if (task->IsEnable() && task->IsShow())
		{
			task->Render();
		}
	}
}
