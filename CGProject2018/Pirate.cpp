#include "Pirate.h"
#include "GeometryNode.h"

Pirate::Pirate(){
	this->x_pirate = 0;
	this->y_pirate = 0;
	this->target_x = 0;
	this->target_y = 0;
	this->roadIdx = 0;
	m_geometric_objectBody = nullptr;
	m_geometric_objectSword = nullptr;
	m_geometric_objectLeftFoot = nullptr;
	m_geometric_objectRightFoot = nullptr;
}

Pirate::~Pirate()
{
	delete m_geometric_objectBody;
	delete m_geometric_objectSword;
	delete m_geometric_objectLeftFoot;
	delete m_geometric_objectRightFoot;
}

void Pirate::setX(float x) {
	this->x_pirate = x;
}

void Pirate::setY(float y) {
	this->y_pirate = y;
}

void Pirate::setTargetX(float x)
{
	this->target_x = x;
}

void Pirate::setTargetY(float y)
{
	this->target_y = y;
}

void Pirate::setRoadIdx(int idx)
{
	this->roadIdx = idx;
}

void Pirate::setBody(GeometryNode * body){
	this->m_geometric_objectBody = body;
}

void Pirate::setBodyTM(glm::mat4 tm){
	this->m_geometric_objectBody_transformation_matrix = tm;
}

void Pirate::setBodyTNM(glm::mat4 tnm){
	this->m_geometric_objectBody_transformation_normal_matrix = tnm;
}

void Pirate::setSword(GeometryNode * sword){
	this->m_geometric_objectSword = sword;
}

void Pirate::setSwordTM(glm::mat4 tm){
	this->m_geometric_objectSword_transformation_matrix = tm;
}

void Pirate::setSwordTNM(glm::mat4 tnm){
	this->m_geometric_objectSword_transformation_normal_matrix = tnm;
}

void Pirate::setLeftFoot(GeometryNode * leftfoot){
	this->m_geometric_objectLeftFoot = leftfoot;
}

void Pirate::setLeftFootTM(glm::mat4 tm){
	this->m_geometric_objectLeftFoot_transformation_matrix = tm;
}

void Pirate::setLeftFootTNM(glm::mat4 tnm){
	this->m_geometric_objectLeftFoot_transformation_normal_matrix = tnm;
}

void Pirate::setRightFoot(GeometryNode * rightfoot){
	this->m_geometric_objectRightFoot = rightfoot;
}

void Pirate::setRightFootTM(glm::mat4 tm){
	this->m_geometric_objectRightFoot_transformation_matrix = tm;
}

void Pirate::setRightFootTNM(glm::mat4 tnm){
	this->m_geometric_objectRightFoot_transformation_normal_matrix = tnm;
}

float Pirate::getX() {
	return this->x_pirate;
}

float Pirate::getY() {
	return this->y_pirate;
}

float Pirate::getTargetX()
{
	return target_x;
}

float Pirate::getTargetY()
{
	return target_y;
}

int Pirate::getRoadIdx()
{
	return roadIdx;
}

GeometryNode * Pirate::getBody()
{
	return m_geometric_objectBody;
}

glm::mat4 Pirate::getBodyTM()
{
	return m_geometric_objectBody_transformation_matrix;
}

glm::mat4 Pirate::getBodyTNM()
{
	return m_geometric_objectBody_transformation_normal_matrix;
}

GeometryNode * Pirate::getSword()
{
	return m_geometric_objectSword;
}

glm::mat4 Pirate::getSwordTM()
{
	return m_geometric_objectSword_transformation_matrix;
}

glm::mat4 Pirate::getSwordTNM()
{
	return m_geometric_objectSword_transformation_normal_matrix;
}

GeometryNode * Pirate::getLeftFoot()
{
	return m_geometric_objectLeftFoot;
}

glm::mat4 Pirate::getLeftFootTM()
{
	return m_geometric_objectLeftFoot_transformation_matrix;
}

glm::mat4 Pirate::getLeftFootTNM()
{
	return m_geometric_objectLeftFoot_transformation_normal_matrix;
}

GeometryNode * Pirate::getRightFoot()
{
	return m_geometric_objectRightFoot;
}

glm::mat4 Pirate::getRightFootTM()
{
	return m_geometric_objectRightFoot_transformation_matrix;
}

glm::mat4 Pirate::getRightFootTNM()
{
	return m_geometric_objectRightFoot_transformation_normal_matrix;
}
