#include "CannonBall.h"
#include "GeometryNode.h"

CannonBall::CannonBall() {
	// oi sintetagmenes isws na ginontai set ekei poy einai o pirgos poy pirobolaei
	this->x_ball = 0;
	this->y_ball = 0;
	this->z_ball = 0;
	this->speed = 9.0f;

	m_geometric_objectCannonBall = nullptr;

	this->bound_shpere = new BoundingShpere();
	this->bound_shpere->setX(0);
	this->bound_shpere->setY(0);
	this->bound_shpere->setZ(0);
	this->bound_shpere->setRadius(0.1f);

}

CannonBall::~CannonBall() {
	delete m_geometric_objectCannonBall;
	delete bound_shpere;
}

float CannonBall::getX() {
	return this->x_ball;
}

float CannonBall::getY() {
	return this->y_ball;
}

float CannonBall::getZ() {
	return this->z_ball;
}

float CannonBall::getSpeed() {
	return this->speed;
}

void CannonBall::setX(float x_ball) {
	this->x_ball = x_ball;
	//8a prepei na kounietai kai to bounding sphere ee?
	//den 3erw poso na to balw omws

}

void CannonBall::setY(float y_ball) {
	this->y_ball = y_ball;
}

void CannonBall::setZ(float z_ball) {
	this->z_ball = z_ball;
}

void CannonBall::setSpeed(float speed) {
	this->speed = speed;
}

void CannonBall::setCannonBall(GeometryNode * ball) {
	this->m_geometric_objectCannonBall = ball;
}

void CannonBall::setCannonBallTM(glm::mat4 tm) {
	this->m_geometric_objectCannonBall_transformation_matrix = tm;
}

void CannonBall::setCannonBallTNM(glm::mat4 tnm) {
	this->m_geometric_objectCannonBall_transformation_normal_matrix = tnm;
}

GeometryNode * CannonBall::getCannonBall(){
	return m_geometric_objectCannonBall;
}

glm::mat4 CannonBall::getCannonBallTM(){
	return m_geometric_objectCannonBall_transformation_matrix;
}

glm::mat4 CannonBall::getCannonBallTNM(){
	return m_geometric_objectCannonBall_transformation_normal_matrix;
}

BoundingShpere* CannonBall::getBoundingSphere()
{
	return bound_shpere;
}