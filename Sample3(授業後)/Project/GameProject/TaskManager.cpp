#include"TaskManager.h"
#include"Task.h"
#include"ObjectBase.h"
//静的なメンバ変数の定義
TaskManager* TaskManager::ms_instance = nullptr;


//コンストラクタ
TaskManager::TaskManager()
{

}

//デストラクタ
TaskManager::~TaskManager()
{
	//すべてのタスクを削除
	DeleteAll();
}

//TaskManagerのインスタンスを取得
TaskManager*TaskManager::Instance()
{
	//インスタンスが生成されてなければ
	//インスタンスを生成後に返す
	if (ms_instance == nullptr)
	{
		ms_instance = new TaskManager();
	}
	return ms_instance;
}
//TaskManagerのインスタンスを破棄
void TaskManager::ClearInstance()
{
	//インスタンスが生成されていたら、削除する
	if (ms_instance != nullptr)
	{
		delete ms_instance;
		ms_instance = nullptr;
	}
}

void TaskManager::Add(Task* task, bool sort)
{
	//並べ替え時の追加処理でなければ「
	if (!sort)
	{
		//追加されるタスクがオブジェクトであれば
		//オブジェクトリストにも登場
		if (task->m_prio == (int)ETaskPrio::Object)
		{
			m_objectList.push_back(task);
		}
	}

	//すべてのタスクを調べて、優先度順に追加する
	auto itr = m_taskuList.begin();
	while (itr != m_taskuList.end())
	{
		Task* curr = *itr;
		//追加するタスクの優先度の数値が低い場合は
		//その位置にタスクを追加する
		if (task->m_prio < curr->m_prio)
		{
			m_taskuList.insert(itr, task);
			return;
		}
		//追加するタスクと現在調べているタスクの優先度が同じ場合は
		//m_sortOrderの順番でリストに追加する
		else if (task->m_prio == curr->m_prio)
		{
			if (task->m_sortOrder<curr->m_sortOrder)
			{
				m_taskuList.insert(itr, task);
				return;
			}
		}
		
		++itr;
	}
	//リストの間に追加する場所が見つからなかったので
	//リストの一番最後に追加
	m_taskuList.push_back(task);
}

void TaskManager::Remove(Task* task, bool sort)
{
	//並び替え時でなければ
	if (!sort)
	{
		//取り除くタスクがオブジェクトならば、オブジェクトからも取り除く
		if (task->m_prio == (int)ETaskPrio::Object)
		{
			m_objectList.remove(task);
		}
	}

	//指定されたタスクをタスクリストから取り除く
	m_taskuList.remove(task);
}

//すべてのタスクを削除
void TaskManager::DeleteAll()
{
	//オブジェクトのリストも空にする
	m_objectList.clear();

	//タスクリストの先頭から順番に削除する
	auto itr = m_taskuList.begin();
	while (itr != m_taskuList.end())
	{
		//削除するタスクのアドレスをいったん記憶し
		//リストから取り除いた後に、タスクを削除する
		Task* del = *itr;
		itr = m_taskuList.erase(itr);
		delete del;
	}
}

void TaskManager::DeleteKilledTasks()
{
	//タスクリストの先頭から順番に削除する
	auto itr = m_taskuList.begin();
	while (itr != m_taskuList.end())
	{
		//削除フラグが立っていたら、削除する
		
		Task* del = *itr;
		if (del->m_isKill)
		{
			itr = m_taskuList.erase(itr);
			delete del;
		}
		else
			//削除フラグが立っていなければ、次のタスクを調べる
		{
			++itr;
		}
	}
}

void TaskManager::Update()
{
	//削除フラグがったっているタスクをすべて削除
	DeleteKilledTasks();
	//リストの先頭から順番に更新処理を呼び出す
	for (Task* task : m_taskuList)
	{
		//タスクが有効であれば、更新
		if (task->IsEnable())
		{
			task->Update();
		}
	}



}

void TaskManager::Render()
{

	m_objectList.sort
	(
		[](const Task* task0, const Task* task1)
		{
			const ObjectBase* obj0 = dynamic_cast<const ObjectBase*>(task0);
			const ObjectBase* obj1 = dynamic_cast<const ObjectBase*>(task1);
			return obj0->GetPos().z < obj1->GetPos().z;
		}
	);
	
	int sortOrder = 0;
	for (Task* obj : m_objectList)
	{
		obj->SetSortOrder(sortOrder);
		sortOrder++;
	}
	

	
	//通常の描画よりも先に呼び出す描画処理
	for (Task* task : m_taskuList)
	{
		//タスクが有効かつ表示状態ならば、描画
		if (task->IsEnable()&&task->IsShow())
		{
			task->PreRender();
		}
	}
	//通常の描画よりも先に呼び出す描画処理
	for (Task* task : m_taskuList)
	{
		//タスクが有効かつ表示状態ならば、描画
		if (task->IsEnable() && task->IsShow())
		{
			task->Render();
		}
	}
}