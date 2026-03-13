#pragma once
#include "Task.h"

class ShutomeCutIn : public Task
{
public:

    ShutomeCutIn(int area);
    ~ShutomeCutIn();

    void Update() override;
    void PreRender() override;

private:

    CImage* mpFace;
    CImage* mpSerif;
    int mTimer;
    int mArea;
};