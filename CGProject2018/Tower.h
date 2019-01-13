#pragma once

#include "GeometryNode.h"

class Tower {

public:
	Tower();
	~Tower();
	
	void setX(float x);
	void setY(float y);

	void setState(int s);

	void setTower(GeometryNode* tower);
	void setTowerTM(glm::mat4 tm);
	void setTowerTNM(glm::mat4 tnm);

	float getX();
	float getY();

	int getState();

	GeometryNode* getTower();
	glm::mat4 getTowerTM();
	glm::mat4 getTowerTNM();

private:
	float x_tower;
	float y_tower;

	int state;

	GeometryNode*									m_geometric_objectTower;
	glm::mat4										m_geometric_objectTower_transformation_matrix;
	glm::mat4										m_geometric_objectTower_transformation_normal_matrix;
};