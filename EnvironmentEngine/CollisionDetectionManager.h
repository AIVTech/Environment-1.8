#pragma once

#include "AABB.h"

class CollisionDetectionManager
{
public:
	CollisionDetectionManager();

	static bool colliding(AABB* first, AABB* second);

	~CollisionDetectionManager();
};

