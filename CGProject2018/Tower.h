#include "GeometryNode.h"

class Tower : public GeometryNode{

public:
	Tower();
	//~Tower();
	
	void setX(float x);
	void setY(float y);

	float getX();
	float getY();

private:
	float x_tower;
	float y_tower;
};