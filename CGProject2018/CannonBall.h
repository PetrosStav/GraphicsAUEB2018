#pragma once

#include "GeometryNode.h"
#include "GeometricMesh.h"
#include "BoundingSphere.h"
#include "Pirate.h"

class CannonBall {

public:
	CannonBall();
	~CannonBall();

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setSpeed(float speed);

	void setTargetX(float x);
	void setTargetY(float y);
	void setTargetZ(float z);

	void setHitTarget(bool hitTarget);

	void setTargetPirate(Pirate* pirate);

	void setCannonBall(GeometryNode* cannonball);
	void setCannonBallTM(glm::mat4 tm);
	void setCannonBallTNM(glm::mat4 tnm);

	float getX();
	float getY();
	float getZ();
	float getSpeed();

	float getTargetX();
	float getTargetY();
	float getTargetZ();

	bool hasHitTarget();

	Pirate* getTargetPirate();

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

	float target_x;
	float target_y;
	float target_z;
	
	Pirate* targetPirate;

	float speed;

	BoundingShpere*									bound_shpere;

	bool hitTarget;

};
