#include "Pirate.h"
#include "GeometryNode.h"

Pirate::Pirate(){
	this->x_pirate = 0;
	this->y_pirate = 0;
	this->target_x = 0;
	this->target_y = 0;
	this->roadIdx = 0;
	this->start_health = 100;
	this->health_points = 100;
	this->dead = false;
	this->goo = false;
	this->dead_cycle = 0;
	this->size = 1.f;
	// speed after 2 starts doing funny stuff
	this->speed = 1.f;
	this->animStart = std::rand() % 1000;
	m_geometric_objectBody = nullptr;
	m_geometric_objectSword = nullptr;
	m_geometric_objectLeftFoot = nullptr;
	m_geometric_objectRightFoot = nullptr;
	m_geometric_objectHealthGreen = nullptr;
	m_geometric_objectHealthRed = nullptr;
	this->bound_shpere = new BoundingShpere();
	this->bound_shpere->setX(18);
	this->bound_shpere->setY(size * 0.7f);
	this->bound_shpere->setZ(18);
	this->bound_shpere->setRadius(size * 12.87075f * 0.09f); // recommended by pdf
	//this->bound_shpere->setRadius(5 * 0.09f);
	m_particle_emitter = new ParticleEmitter();
	m_particle_emitter->Init();
	m_particle_emitter->setTreasureChest(false);
}

Pirate::~Pirate()
{
	delete m_geometric_objectBody;
	delete m_geometric_objectSword;
	delete m_geometric_objectLeftFoot;
	delete m_geometric_objectRightFoot;
	delete m_geometric_objectHealthGreen;
	delete m_geometric_objectHealthRed;
	delete bound_shpere;
	delete m_particle_emitter;
}

void Pirate::setX(float x) {
	this->x_pirate = x;
	// Change bounding sphere X pos
	this->bound_shpere->setX(18 + 4 * x);
}

void Pirate::setY(float y) {
	this->y_pirate = y;
	// Change bounding sphere Z pos
	this->bound_shpere->setZ(18 + 4 * y);
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

void Pirate::setStartHealth(int hp)
{
	start_health = hp;
}

void Pirate::setHealthPoints(int hp)
{
	this->health_points = hp;
}

void Pirate::setSpeed(float speed)
{
	this->speed = speed;
}

void Pirate::setAnimStart(int start)
{
	this->animStart = start;
}

void Pirate::setSize(float size)
{
	this->size = size;
}

void Pirate::setType(int type)
{
	this->type = type;
}

void Pirate::setLevel(int level)
{
	this->level = level;
}

void Pirate::setDir(int dir)
{
	this->dir = dir;
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

void Pirate::setHealthGreen(GeometryNode * healthgreen)
{
	m_geometric_objectHealthGreen = healthgreen;
}

void Pirate::setHealthGreenTM(glm::mat4 tm)
{
	m_geometric_objectHealthGreen_transformation_matrix = tm;
}

void Pirate::setHealthGreenTNM(glm::mat4 tnm)
{
	m_geometric_objectHealthGreen_transformation_normal_matrix = tnm;
}

void Pirate::setHealthRed(GeometryNode * healthred)
{
	m_geometric_objectHealthRed = healthred;
}

void Pirate::setHealthRedTM(glm::mat4 tm)
{
	m_geometric_objectHealthRed_transformation_matrix = tm;
}

void Pirate::setHealthRedTNM(glm::mat4 tnm)
{
	m_geometric_objectHealthRed_transformation_normal_matrix = tnm;
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

int Pirate::getStartHealth()
{
	return start_health;
}

int Pirate::getHealthPoints()
{
	return health_points;
}

bool Pirate::isDead()
{
	return dead;
}

void Pirate::setDead(bool state)
{
	dead = state;
}

bool Pirate::isGoo()
{
	return goo;
}

void Pirate::setGoo(bool state)
{
	goo = state;
}

void Pirate::setDeadCycle(int i)
{
	dead_cycle = i;
}

int Pirate::getDeadCycle()
{
	return dead_cycle;
}

float Pirate::getSpeed()
{
	return speed;
}

int Pirate::getAnimStart()
{
	return animStart;
}

float Pirate::getSize()
{
	return size;
}

int Pirate::getType()
{
	return type;
}

int Pirate::getLevel()
{
	return level;
}

int Pirate::getDir()
{
	return dir;
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

GeometryNode * Pirate::getHealthGreen()
{
	return m_geometric_objectHealthGreen;
}

glm::mat4 Pirate::getHealthGreenTM()
{
	return m_geometric_objectHealthGreen_transformation_matrix;
}

glm::mat4 Pirate::getHealthGreenTNM()
{
	return m_geometric_objectHealthGreen_transformation_normal_matrix;
}

GeometryNode * Pirate::getHealthRed()
{
	return m_geometric_objectHealthRed;
}

glm::mat4 Pirate::getHealthRedTM()
{
	return m_geometric_objectHealthRed_transformation_matrix;
}

glm::mat4 Pirate::getHealthRedTNM()
{
	return m_geometric_objectHealthRed_transformation_normal_matrix;
}

BoundingShpere* Pirate::getBoundingSphere()
{
	return bound_shpere;
}

ParticleEmitter * Pirate::getParticleEmmiter()
{
	return m_particle_emitter;
}
