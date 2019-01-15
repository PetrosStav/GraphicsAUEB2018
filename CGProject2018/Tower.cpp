#include "Tower.h"
#include "GeometryNode.h"

Tower::Tower() {
	this->x_tower = 0;
	this->y_tower = 0;
	this->state = 0;
	this->fireRate = 1000;
	this->damage = 10;
	this->level = 1;
	this->range = 2;
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

void Tower::setFireRate(int rate)
{
	fireRate = rate;
}

void Tower::setDamage(int damage)
{
	this->damage = damage;
}

void Tower::setLevel(int level)
{
	this->level = level;
}

void Tower::setRange(int range)
{
	this->range = range;
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

int Tower::getFireRate()
{
	return fireRate;
}

int Tower::getDamage()
{
	return damage;
}

int Tower::getLevel()
{
	return level;
}

int Tower::getRange()
{
	return range;
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

