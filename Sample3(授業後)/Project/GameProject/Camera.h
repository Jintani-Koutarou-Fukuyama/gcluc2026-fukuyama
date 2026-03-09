#pragma once
#include "Task.h"
#include"GLLibrary.h"

class Camera : public Task
{
public:
    static Camera* Instance();

   
    void Update() override;

    
    static const CVector2D& GetOffset();


    static void SetTargetPos(const CVector3D& s_pos);

private:
    Camera();
    ~Camera();

    static Camera* mInstance;

    static CVector2D mOffset;      // 描画オフセット
    static CVector3D mTargetPos;   // プレイヤーのワールド座標

    float mCameraX;                // カメラの中心X
};