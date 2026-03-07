#include "Task.h"
#include"TaskManager.h"


//コンストラクタ
Task::Task(int s_prio, int s_sortOrder)
	:mIsEnable(true)
	,mIsShow(true)
	,mIsKill(false)
	,mPrio(s_prio)
	,mSortOrder(s_sortOrder)
{
	//タスク生成時にTaskManagerのタスクリストに自身を追加
	TaskManager::Instance()->Add(this);
}

//デストラクタ
Task::~Task()
{
	//タスクは破棄時にTaskManagerのタスクリストから自身を取り除く
	TaskManager::Instance()->Remove(this);
}

//有効フラグを設定
void Task::SetEnable(bool s_enable)
{
	mIsEnable = s_enable;
}

//有効フラグを取得
bool Task::IsEnable() const
{
	return mIsEnable;
}

//表示フラグを設定
void Task::SetShow(bool s_show)
{
	mIsShow = s_show;
}

//表示フラグを取得
bool Task::IsShow() const
{
	return mIsShow;
}

//タスクを削除
void Task::Kill()
{
	mIsKill = true;
}

//削除フラグが立っているか
bool Task::IsKill() const
{
	return mIsKill;
}

//優先度を設定
void Task::SetPriority(int s_prio)
{
	if (s_prio == mPrio)return;

	//新しい優先度を設定
	mPrio = s_prio;
	//一度タスクリストから取り除いて、再度追加しなおすことで並べ替える
	TaskManager::Instance()->Remove(this, true);
	TaskManager::Instance()->Add(this, true);
}

//優先度を取得
int Task::GetPriority() const
{
	return mPrio;
}

//優先度内の順番を設定
void Task::SetSortOrder(int s_order)
{
	//設定された順番が同じであれば、処理しない
	if (s_order == mSortOrder) return;

	//優先度内の順番を設定
	mSortOrder = s_order;
	//一度タスクリストから取り除いて、再度追加しなおすことで並べ替える
	TaskManager::Instance()->Remove(this, true);
	TaskManager::Instance()->Add(this, true);
}

//優先度内の順番を取得
int Task::GetSortOrder() const
{
	return mSortOrder;
}

//更新処理（継承先で使用）
void Task:: Update()
{

}

//通常の描画処理より前に実装する描画処理（影描画用、継承先で使用）
void Task::PreRender()
{
}



//描画処理（継承先で使用）
void Task::Render()
{

}
