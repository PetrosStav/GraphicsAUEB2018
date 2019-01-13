#pragma once

#include "Tower.h"
#include "Pirate.h"
#include "CannonBall.h"
#include "GeometricMesh.h"

class GameState {
public:

	GameState();
	~GameState();

	void setGold(unsigned int gold);
	unsigned int getGold();

	void setScore(unsigned int score);
	unsigned int getScore();

	void setAvailableTowers(std::vector<Tower*> availableTowers);
	std::vector<Tower*> getAvailableTowers();

	void setCreatedTowers(std::vector<Tower*> createdTowers);
	std::vector<Tower*> getCreatedTowers();

	void setPirates(std::vector<Pirate*> pirates);
	std::vector<Pirate*> getPirates();

	void setCannonBalls(std::vector<CannonBall*> cannonballs);
	std::vector<CannonBall*> getCannonBalls();

	std::tuple<int, int>* getRoadTiles();

	// Tower functions
	void										addTower(float x, float y);
	void										addTower();

	void										removeTower(float x, float y);
	void										removeTower();

	void										rearrangeTower(float x, float y);
	void										rearrangeTower();

	// Grid functions
	void										getRealPos(float& x, float& y);
	void										getGridPos(float& x, float& y);

	// Tile Functions
	void										setTilePosition(int x, int y);
	void										setTileX(int x);
	void										setTileY(int y);
	int											getTileX();
	int											getTileY();

	void										updateInRoad();
	bool										getInRoad();
	bool										isInRoad(int x, int y);

	// Meshes

	void										setPirateBodyMesh(GeometricMesh* mesh);
	void										setPirateSwordMesh(GeometricMesh* mesh);
	void										setPirateLFootMesh(GeometricMesh* mesh);
	void										setPirateRFootMesh(GeometricMesh* mesh);
	void										assignMeshtoPirates();

	void										setTowerMesh(GeometricMesh* mesh);
	void										assignMeshToTowers();

	void										setCannonballMesh(GeometricMesh* mesh);

	// Adding objects

	void										createTower();
	void										createPirate();
	void										shootCannonBall(Tower* tower, Pirate* pirate);

	// Update paths

	void										updatePirateTargets();

	// 

	void										deleteHitCannonBall(CannonBall* cannonball);
	void										deleteHitCannonBalls();

	void										towersFire();

	void										deletePirate(Pirate* pirate);

private:

	// Tile positions
	int											tileX, tileY;

	// Game variables
	unsigned int								score;
	unsigned int								gold;

	// Towers
	std::vector<Tower*>							availableTowers;
	std::vector<Tower*>							createdTowers;

	// Pirates
	std::vector<Pirate*>						pirates;

	// Cannonballs
	std::vector<CannonBall*>					cannonballs;

	// Road Tile List
	std::tuple<int, int>						road_tiles[29];

	bool										inRoad;

	// Meshes
	GeometricMesh*								pirateBodyMesh;
	GeometricMesh*								pirateSwordMesh;
	GeometricMesh*								pirateLFootMesh;
	GeometricMesh*								pirateRFootMesh;

	GeometricMesh*								towerMesh;

	GeometricMesh*								cannonballMesh;

};