#pragma once

#include "Transform.h"

class Actor
{
public:
	Actor() = default;
	~Actor() = default;

	virtual void Update();

private:
	Transform transform;
};

