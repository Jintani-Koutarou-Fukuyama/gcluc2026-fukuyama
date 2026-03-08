#include "Camera.h"
#include"Field.h"

Camera* Camera::mInstance = nullptr;
CVector2D Camera::mOffset = CVector2D::zero;
CVector3D Camera::mTargetPos = CVector3D::zero;

Camera::Camera()
    : Task((int)ETaskPrio::EFIELD - 1) // フィールドより前に更新
    , mCameraX(0.0f)
{
}

Camera::~Camera()
{
}

Camera* Camera::Instance()
{
    if (mInstance == nullptr)
    {
        mInstance = new Camera();
    }
    return mInstance;
}

void Camera::SetTargetPos(const CVector3D& s_pos)
{
    mTargetPos = s_pos;
}

const CVector2D& Camera::GetOffset()
{
    return mOffset;
}

void Camera::Update()
{
    // プレイヤーを画面中央に置く
    float targetX = mTargetPos.x - SCREEN_WIDTH * 0.5f;

    // スムーズ追従（リニア）
    mCameraX += (targetX - mCameraX) * 0.1f;

    // スクロール制限（左端）
    if (mCameraX < 0) mCameraX = 0;
   
    //↓画像の大きさに自動で合わせてくれるようになったと思う
    // スクロール制限（右端）
    float maxX = Field::sFieldWidth - SCREEN_WIDTH;

    if (mCameraX > maxX)
        mCameraX = maxX;


    
    mOffset.x = -mCameraX;
    mOffset.y = 0;
   
}