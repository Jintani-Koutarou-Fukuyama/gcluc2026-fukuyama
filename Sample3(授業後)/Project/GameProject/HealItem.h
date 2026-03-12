#pragma once
#pragma once
#include "ObjectBase.h"
//‰ñ•œ–ò‚ÌƒNƒ‰ƒX

class HealItem : public ObjectBase
{
public:

	HealItem(const CVector3D& pos);

	void Update() override;
	void Render() override;

private:

	CImage* mpImage;
	float mFloatTime;
};