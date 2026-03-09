#pragma once

class TaskManager;
//タスクの優先度の種類
enum class ETaskPrio
{
	EMANAGER,//マネージャー関連

	EFIELD,//フィールド
	ESHADOW,//影
	EOBJECT,//オブジェクト（プレイヤーや敵など）
	EUI,//UI（HPやタイマー、文字など）

};

class Task
{
	friend TaskManager;

public:
	//コンストラクタ
	Task(int s_prio,int s_sortOrder=0);
	//デストラクタ
	virtual ~Task();

	//有効フラグを設定
	void SetEnable(bool s_enable);
	//有効フラグを取得
	bool IsEnable() const;

	//表示フラグを設定
	void SetShow(bool s_show);
	//表示フラグを取得
	bool IsShow() const;

	//タスクを削除
	void Kill();
	//削除フラグが立っているか
	bool IsKill()const;

	//優先度を設定
	void SetPriority(int s_prio);
	//優先度を取得
	int GetPriority()const;

	//優先度内の順番を設定
	void SetSortOrder(int s_order);
	//優先度内の順番を取得
	int GetSortOrder()const;

	//更新処理（継承先で使用）
	virtual void Update();
	//通常の描画処理より前に実装する描画処理（影描画用、継承先で使用）
	virtual void PreRender();
	//描画処理（継承先で使用）
	virtual void Render();

private:
	bool mIsEnable;//有効フラグ
	bool mIsShow;//表示フラグ
	bool mIsKill;//削除フラグ
	int mPrio;//タスクの優先度
	int mSortOrder;//同じ優先度内での順番
};