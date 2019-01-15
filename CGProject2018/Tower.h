#pragma once

#include "GeometryNode.h"

class Tower {

public:
	Tower();
	~Tower();
	
	void setX(float x);
	void setY(float y);

	void setState(int s);
	void setFireRate(int rate);
	void setDamage(int damage);
	void setLevel(int level);
	void setRange(int range);

	void setTower(GeometryNode* tower);
	void setTowerTM(glm::mat4 tm);
	void setTowerTNM(glm::mat4 tnm);

	float getX();
	float getY();

	int getState();
	int getFireRate();

	int getDamage();

	int getLevel();

	int getRange();

	GeometryNode* getTower();
	glm::mat4 getTowerTM();
	glm::mat4 getTowerTNM();

private:
	float x_tower;
	float y_tower;

	int state;

	// Fire Rate is connected with States
	// If fire rate is 1000 it means it fires every 1000 ms
	// If fire rate is 100 (lowest) it fires every 100 ms
	int fireRate;

	int damage;

	int level;

	int range;

	GeometryNode*									m_geometric_objectTower;
	glm::mat4										m_geometric_objectTower_transformation_matrix;
	glm::mat4										m_geometric_objectTower_transformation_normal_matrix;
};