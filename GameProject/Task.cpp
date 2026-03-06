#include "Task.h"
#include "TaskManager.h"

Task::Task(int prio, int sortOrder)
	: m_isEnable(true)
	, m_isShow(true)
	, m_isKill(false)
	, m_prio(prio)
	, m_sortOrder(sortOrder)
{
	//Task生成時にTaskManagerのタスクリストに自身を追加
	TaskManager::Instance()->Add(this);
}

//デストラクタ
Task::~Task()
{
	//Task破棄時にTaskManagerのタスクリストから自身を取り除く
	TaskManager::Instance()->Remove(this);
}

//有効フラグを設定
void Task::SetEnable(bool enable)
{
	m_isEnable = enable;
}

bool Task::IsEnable() const
{
	return m_isEnable;
}

//表示フラグを設定
void Task::SetShow(bool show)
{
	m_isShow = show;
}

//表示フラグを取得
bool Task::IsShow() const
{
	return m_isShow;
}

//タスクを削除
void Task::Kill()
{
	m_isKill = true;
}

//削除フラグが立っているか
bool Task::IsKill() const
{
	return m_isKill;
}

//優先度を設定
void Task::SetPriority(int prio)
{
	//設定された優先度が同じであれば、処理しない
	if (prio == m_prio) return;

	//新しい優先度を設定
	m_prio = prio;
	//一度タスクリストから取り除いて、再度追加しなおすことで並び替える
	TaskManager::Instance()->Remove(this, true);
	TaskManager::Instance()->Add(this, true);
}

//優先度を取得
int Task::GetPriority() const
{
	return m_prio;
}

//優先度内の順番を設定
void Task::SetSortOrder(int order)
{
	if (order == m_sortOrder) return;
	//優先度内の順番を設定
	m_sortOrder = order;
	//一度タスクリストから取り除いて、再度追加しなおすことで並び替える
	TaskManager::Instance()->Remove(this, true);
	TaskManager::Instance()->Add(this, true);

}

//優先度内の順番を取得
int Task::GetSortOrder() const
{
	return m_sortOrder;
}

void Task::Update()
{

}

void Task::PreRender()
{
}

void Task::Render()
{

}