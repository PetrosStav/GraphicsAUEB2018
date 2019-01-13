#include "Tower.h"
#include "GeometryNode.h"

Tower::Tower() {
	this->x_tower = 0;
	this->y_tower = 0;
	this->state = 0;
	m_geometric_objectTower = nullptr;
}

Tower::~Tower() {
	delete m_geometric_objectTower;
}

void Tower::setX(float x) {
	this->x_tower = x;
}

void Tower::setY(float y) {
	this->y_tower = y;
}

void Tower::setState(int s)
{
	this->state = s;
}

void Tower::setTower(GeometryNode * tower) {
	this->m_geometric_objectTower = tower;
}

void Tower::setTowerTM(glm::mat4 tm) {
	this->m_geometric_objectTower_transformation_matrix = tm;
}

void Tower::setTowerTNM(glm::mat4 tnm) {
	this->m_geometric_objectTower_transformation_normal_matrix = tnm;
}

float Tower::getX() {
	return this->x_tower;
}

float Tower::getY() {
	return this->y_tower;
}

int Tower::getState()
{
	return state;
}

GeometryNode * Tower::getTower()
{
	return m_geometric_objectTower;
}

glm::mat4 Tower::getTowerTM()
{
	return m_geometric_objectTower_transformation_matrix;
}

glm::mat4 Tower::getTowerTNM()
{
	return m_geometric_objectTower_transformation_normal_matrix;
}

