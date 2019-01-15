#pragma once

#include "GeometryNode.h"
#include "BoundingSphere.h"

class TreasureChest {

public:

	TreasureChest();
	~TreasureChest();

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	void setChest(GeometryNode* chest);
	void setChestTM(glm::mat4 tm);
	void setChestTNM(glm::mat4 tnm);

	float getX();
	float getY();
	float getZ();

	GeometryNode* getChest();
	glm::mat4 getChestTM();
	glm::mat4 getChestTNM();

	BoundingShpere* getBoundingSphere();

private:

	float x_chest;
	float y_chest;
	float z_chest;

	GeometryNode*									m_geometric_objectChest;
	glm::mat4										m_geometric_objectChest_transformation_matrix;
	glm::mat4										m_geometric_objectChest_transformation_normal_matrix;

	BoundingShpere*									bound_shpere;

};