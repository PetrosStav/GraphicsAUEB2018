#pragma once

class BoundingShpere {

public:

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setRadius(float r);

	float getX();
	float getY();
	float getZ();
	float getRadius();

	bool isObjectIntersecting(const float &obj_x,const float &obj_y,const float &obj_z) const;

	bool isSphereIntersecting(BoundingShpere* sphere) const;

private:

	float x, y, z, radius;

};