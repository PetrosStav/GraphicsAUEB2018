#include "BoundingSphere.h"
#include <math.h>

void BoundingShpere::setX(float x)
{
	this->x = x;
}

void BoundingShpere::setY(float y)
{
	this->y = y;
}

void BoundingShpere::setZ(float z)
{
	this->z = z;
}

void BoundingShpere::setRadius(float r)
{
	this->radius = r;
}

float BoundingShpere::getX()
{
	return x;
}

float BoundingShpere::getY()
{
	return y;
}

float BoundingShpere::getZ()
{
	return z;
}

float BoundingShpere::getRadius()
{
	return radius;
}

bool BoundingShpere::isObjectIntersecting(const float & obj_x, const float & obj_y, const float & obj_z) const
{
	float sum = pow((x - obj_x), 2) + pow((y - obj_y), 2) + pow((z - obj_z), 2);
	return sqrt(sum) <= radius;
}

bool BoundingShpere::isSphereIntersecting(BoundingShpere * sphere) const
{
	float distance = sqrt(pow((x - sphere->getX()), 2) + pow((y - sphere->getY()), 2) + pow((z - sphere->getZ()), 2));
	return distance <= (radius + sphere->getRadius());
}
