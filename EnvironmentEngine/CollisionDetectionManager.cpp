#include "CollisionDetectionManager.h"

CollisionDetectionManager::CollisionDetectionManager()
{
}

CollisionDetectionManager::~CollisionDetectionManager()
{
}

bool CollisionDetectionManager::colliding(AABB* first, AABB* second)
{
	bool xAxis = false;
	bool yAxis = false;
	bool zAxis = false;

	if ((first->xMax < second->xMax && first->xMax > second->xMin) ||
		(first->xMin > second->xMin && first->xMin < second->xMax))
	{
		xAxis = true;
	}

	if ((first->yMax < second->yMax && first->yMax > second->yMin) ||
		(first->yMin > second->yMin && first->yMin < second->yMax))
	{
		yAxis = true;
	}

	if ((first->zMax < second->zMax && first->zMax > second->zMin) ||
		(first->zMin > second->zMin && first->zMin < second->zMax))
	{
		zAxis = true;
	}

	if (xAxis && yAxis && zAxis)
	{
		return true;
	}
	return false;
}
