#pragma once

#include "GeometryNode.h"
#include "GeometricMesh.h"

class Pirate{

public:
	Pirate();
	~Pirate();

	void setX(float x);
	void setY(float y);
	void setTargetX(float x);
	void setTargetY(float y);
	void setRoadIdx(int idx);

	void setBody(GeometryNode* body);
	void setBodyTM(glm::mat4 tm);
	void setBodyTNM(glm::mat4 tnm);

	void setSword(GeometryNode* sword);
	void setSwordTM(glm::mat4 tm);
	void setSwordTNM(glm::mat4 tnm);

	void setLeftFoot(GeometryNode* leftfoot);
	void setLeftFootTM(glm::mat4 tm);
	void setLeftFootTNM(glm::mat4 tnm);

	void setRightFoot(GeometryNode* rightfoot);
	void setRightFootTM(glm::mat4 tm);
	void setRightFootTNM(glm::mat4 tnm);

	float getX();
	float getY();

	float getTargetX();
	float getTargetY();

	int getRoadIdx();

	GeometryNode* getBody();
	glm::mat4 getBodyTM();
	glm::mat4 getBodyTNM();

	GeometryNode* getSword();
	glm::mat4 getSwordTM();
	glm::mat4 getSwordTNM();

	GeometryNode* getLeftFoot();
	glm::mat4 getLeftFootTM();
	glm::mat4 getLeftFootTNM();

	GeometryNode* getRightFoot();
	glm::mat4 getRightFootTM();
	glm::mat4 getRightFootTNM();


private:

	GeometryNode*									m_geometric_objectBody;
	glm::mat4										m_geometric_objectBody_transformation_matrix;
	glm::mat4										m_geometric_objectBody_transformation_normal_matrix;
	
	GeometryNode*									m_geometric_objectSword;
	glm::mat4										m_geometric_objectSword_transformation_matrix;
	glm::mat4										m_geometric_objectSword_transformation_normal_matrix;

	GeometryNode*									m_geometric_objectLeftFoot;
	glm::mat4										m_geometric_objectLeftFoot_transformation_matrix;
	glm::mat4										m_geometric_objectLeftFoot_transformation_normal_matrix;

	GeometryNode*									m_geometric_objectRightFoot;
	glm::mat4										m_geometric_objectRightFoot_transformation_matrix;
	glm::mat4										m_geometric_objectRightFoot_transformation_normal_matrix;

	GeometricMesh*									obj_mesh;

	float x_pirate;
	float y_pirate;

	float target_x;
	float target_y;

	int roadIdx;

};