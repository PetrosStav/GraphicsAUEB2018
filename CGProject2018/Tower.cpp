#include "Tower.h"
#include "GeometryNode.h"

Tower::Tower() : GeometryNode() {
	this->x_tower = 0;
	this->y_tower = 0;
}

//Tower::~Tower() { }

void Tower::setX(float x) {
	this->x_tower = x;
}

void Tower::setY(float y) {
	this->y_tower = y;
}

float Tower::getX() {
	return this->x_tower;
}

float Tower::getY() {
	return this->y_tower;
}
