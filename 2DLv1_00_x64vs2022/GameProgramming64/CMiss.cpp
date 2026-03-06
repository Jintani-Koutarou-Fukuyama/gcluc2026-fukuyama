#include "CMiss.h"

bool CMiss::Collision(CRectangle* rect)
{
	if (CRectangle::Collision(rect))
	{
		mState = EState::ESTOP;
		return true;
	}
	return false;
}
