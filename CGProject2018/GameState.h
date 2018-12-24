#pragma once

#include "Tower.h"
#include "Pirate.h"
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

	std::tuple<int, int>* getRoadTiles();

	// Tower functions
	void										addTower(float x, float y);
	void										addTower();

	void										removeTower(float x, float y);
	void										removeTower();

	void										rearrangeTower(float x, float y);
	void										rearrangeTower();

	// Grid function
	void										getRealPos(float& x, float& y);

	// Green tile Function
	void										setTilePosition(int x, int y);
	void										setTileX(int x);
	void										setTileY(int y);
	int											getTileX();
	int											getTileY();

	void										updateInRoad();
	bool										getInRoad();
	bool										isInRoad(int x, int y);

	void										setPirateBodyMesh(GeometricMesh* mesh);
	void										setPirateSwordMesh(GeometricMesh* mesh);
	void										setPirateLFootMesh(GeometricMesh* mesh);
	void										setPirateRFootMesh(GeometricMesh* mesh);

	void										assignMeshtoPirates();

	void										createPirate();

	void										setTowerMesh(GeometricMesh* mesh);

	void										assignMeshToTowers();

	void										createTower();

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

	// Road Tile List
	std::tuple<int, int>						road_tiles[29];

	bool										inRoad;

	// Meshes
	GeometricMesh*								pirateBodyMesh;
	GeometricMesh*								pirateSwordMesh;
	GeometricMesh*								pirateLFootMesh;
	GeometricMesh*								pirateRFootMesh;

	GeometricMesh*								towerMesh;

};