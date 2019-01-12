#pragma once

#include "GeometryNode.h"
#include "GeometricMesh.h"
#include "BoundingSphere.h"

class CannonBall {

public:
	CannonBall();
	~CannonBall();

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setSpeed(float speed);


	void setCannonBall(GeometryNode* cannonball);
	void setCannonBallTM(glm::mat4 tm);
	void setCannonBallTNM(glm::mat4 tnm);

	float getX();
	float getY();
	float getZ();
	float getSpeed();

	GeometryNode* getCannonBall();
	glm::mat4 getCannonBallTM();
	glm::mat4 getCannonBallTNM();

	BoundingShpere* getBoundingSphere();

private:

	GeometryNode*									m_geometric_objectCannonBall;
	glm::mat4										m_geometric_objectCannonBall_transformation_matrix;
	glm::mat4										m_geometric_objectCannonBall_transformation_normal_matrix;

	float x_ball;
	float y_ball;
	float z_ball;
	float speed;

	BoundingShpere*									bound_shpere;


};
