#include "TreasureChest.h"

TreasureChest::TreasureChest() {
	this->x_chest = -3.f;
	this->y_chest = 0;
	this->z_chest = 10.f;
	m_geometric_objectChest = nullptr;
	this->bound_shpere = new BoundingShpere();
	this->bound_shpere->setX(36 - 2*x_chest);
	this->bound_shpere->setY(y_chest);
	this->bound_shpere->setZ(36 - 2*z_chest);
	this->bound_shpere->setRadius(12.0284f * 0.09f);
}

TreasureChest::~TreasureChest() {
	delete m_geometric_objectChest;
	delete bound_shpere;
}

void TreasureChest::setX(float x)
{
	this->x_chest = x;
	this->bound_shpere->setX(36 - 2 *x_chest);
}

void TreasureChest::setY(float y)
{
	this->y_chest = y;
	this->bound_shpere->setY(y_chest);
}

void TreasureChest::setZ(float z)
{
	this->z_chest = z;
	this->bound_shpere->setZ(36 - 2*z_chest);
}

void TreasureChest::setChest(GeometryNode * chest)
{
	this->m_geometric_objectChest = chest;
}

void TreasureChest::setChestTM(glm::mat4 tm)
{
	this->m_geometric_objectChest_transformation_matrix = tm;
}

void TreasureChest::setChestTNM(glm::mat4 tnm)
{
	this->m_geometric_objectChest_transformation_normal_matrix = tnm;
}

float TreasureChest::getX()
{
	return x_chest;
}

float TreasureChest::getY()
{
	return y_chest;
}

float TreasureChest::getZ()
{
	return z_chest;
}

GeometryNode * TreasureChest::getChest()
{
	return m_geometric_objectChest;
}

glm::mat4 TreasureChest::getChestTM()
{
	return m_geometric_objectChest_transformation_matrix;
}

glm::mat4 TreasureChest::getChestTNM()
{
	return m_geometric_objectChest_transformation_normal_matrix;
}

BoundingShpere * TreasureChest::getBoundingSphere()
{
	return bound_shpere;
}
