#pragma once
#include "ObjectBase.h"

class Obstacle : public ObjectBase
{
public:

    Obstacle(const CVector3D& pos);

    void Update() override;
    void Render() override;

private:

    CImage* mpImage;

};