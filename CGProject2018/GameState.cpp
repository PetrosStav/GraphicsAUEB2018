#include "GameState.h"

GameState::GameState() {
	// Initialize everything
	score = 0;
	gold = 100;
	pirateWave = 0;
	pirateSubWave = 1;
	pirateRate = 2000;
	availableTowers = std::vector<Tower*>();
	createdTowers = std::vector<Tower*>();
	pirates = std::vector<Pirate*>();
	cannonballs = std::vector<CannonBall*>();
	treasureChest = new TreasureChest();
	musicManager = MusicManager::Instance();

	gameOver = false;
	paused = false;
	wasPaused = false;
	stopWaves = false;
	isDarth = false;
	wasDarth = false;
	boss = false;
	showGoldParticles = false;

	actions = 90;

	// Testing

	// Create a pirate at position 0,0
	/*Pirate* p1 = new Pirate();
	p1->setX(0);
	p1->setY(0);
	pirates.push_back(p1);*/

	//// Create a pirate at position 1,1
	//Pirate* p2 = new Pirate();
	//p2->setX(1);
	//p2->setY(1);
	//pirates.push_back(p2);

	// Start with 3 available towers

	for (unsigned i = 0; i < 3; i++) {
		Tower* t = new Tower();
		availableTowers.push_back(t);
	}

	// Set green tile to center of screen
	tileX = 4;
	tileY = 4;

	updateInRoad();

	// Initialize road tiles
	road_tiles[0] = std::tuple<int, int>(0, 0);
	road_tiles[1] = std::tuple<int, int>(0, 1);
	road_tiles[2] = std::tuple<int, int>(0, 2);
	road_tiles[3] = std::tuple<int, int>(0, 3);
	road_tiles[4] = std::tuple<int, int>(1, 3);
	road_tiles[5] = std::tuple<int, int>(1, 4);
	road_tiles[6] = std::tuple<int, int>(1, 5);
	road_tiles[7] = std::tuple<int, int>(1, 6);
	road_tiles[8] = std::tuple<int, int>(1, 7);
	road_tiles[9] = std::tuple<int, int>(2, 7);
	road_tiles[10] = std::tuple<int, int>(2, 8);
	road_tiles[11] = std::tuple<int, int>(3, 8);
	road_tiles[12] = std::tuple<int, int>(4, 8);
	road_tiles[13] = std::tuple<int, int>(5, 8);
	road_tiles[14] = std::tuple<int, int>(6, 8);
	road_tiles[15] = std::tuple<int, int>(6, 7);
	road_tiles[16] = std::tuple<int, int>(6, 6);
	road_tiles[17] = std::tuple<int, int>(7, 6);
	road_tiles[18] = std::tuple<int, int>(7, 5);
	road_tiles[19] = std::tuple<int, int>(7, 4);
	road_tiles[20] = std::tuple<int, int>(7, 3);
	road_tiles[21] = std::tuple<int, int>(8, 3);
	road_tiles[22] = std::tuple<int, int>(9, 3);
	road_tiles[23] = std::tuple<int, int>(9, 2);
	road_tiles[24] = std::tuple<int, int>(9, 1);
	road_tiles[25] = std::tuple<int, int>(8, 1);
	road_tiles[26] = std::tuple<int, int>(7, 1);
	road_tiles[27] = std::tuple<int, int>(6, 1);
	road_tiles[28] = std::tuple<int, int>(6, 0);

}

GameState::~GameState()
{
	// delete everything
	MusicManager::Release();
	musicManager = NULL;

	// delete all pirates
	for (Pirate* p : pirates) {
		delete p;
	}

	// delete all towers

	for (Tower* t : availableTowers) {
		delete t;
	}

	for (Tower* t : createdTowers) {
		delete t;
	}

	for (CannonBall* cb : cannonballs) {
		delete cb;
	}

}

void GameState::setGold(unsigned int gold)
{
	this->gold = gold;
}

unsigned int GameState::getGold()
{
	return gold;
}

void GameState::setScore(unsigned int score)
{
	this->score = score;
}

unsigned int GameState::getScore()
{
	return score;
}

void GameState::setPirateWave(unsigned int wave) {
	this->pirateWave = wave;
}

unsigned int GameState::getPirateWave()
{
	return pirateWave;
}

void GameState::setPirateSubWave(unsigned int subwave)
{
	this->pirateSubWave = subwave;
}

unsigned int GameState::getPirateSubWave()
{
	return pirateSubWave;
}

void GameState::setPirateRate(unsigned int rate)
{
	this->pirateRate = rate;
}

unsigned int GameState::getPirateRate()
{
	return pirateRate;
}


void GameState::setAvailableTowers(std::vector<Tower*> availableTowers)
{
	this->availableTowers = availableTowers;
}

std::vector<Tower*> GameState::getAvailableTowers()
{
	return availableTowers;
}

void GameState::setCreatedTowers(std::vector<Tower*> createdTowers)
{
	this->createdTowers = createdTowers;
}

std::vector<Tower*> GameState::getCreatedTowers()
{
	return createdTowers;
}

void GameState::setPirates(std::vector<Pirate*> pirates)
{
	this->pirates = pirates;
}

std::vector<Pirate*> GameState::getPirates()
{
	return pirates;
}

void GameState::setCannonBalls(std::vector<CannonBall*> cannonballs)
{
	this->cannonballs = cannonballs;
}

std::vector<CannonBall*> GameState::getCannonBalls()
{
	return cannonballs;
}

void GameState::setTreasureChest(TreasureChest * chest)
{
	this->treasureChest = chest;
}

TreasureChest * GameState::getTreasureChest()
{
	return treasureChest;
}

std::tuple<int, int>* GameState::getRoadTiles()
{
	return road_tiles;
}

void GameState::setGameOver(bool state)
{
	this->gameOver = state;
}

bool GameState::getGameOver()
{
	return gameOver;
}

void GameState::setPaused(bool state)
{
	this->paused = state;
}

bool GameState::isPaused()
{
	return paused;
}

void GameState::setWasPaused(bool state)
{
	this->wasPaused = state;
}

bool GameState::getWasPaused()
{
	return wasPaused;
}

void GameState::setActions(unsigned int actions)
{
	this->actions = actions;
}

unsigned int GameState::getActions()
{
	return actions;
}

bool GameState::addTower(float x, float y)
{
	if (availableTowers.size() != 0) {
		getRealPos(x, y);
		// Check that no other towers are in this spot
		for (Tower* t : createdTowers) {
			if (t->getX() == x && t->getY() == y) {
				// TODO
				// If we found then [MESSAGE] OR [ANOTHER TILE COLOR] + return
				return false;
			}
		}
		availableTowers.back()->setX(x);
		availableTowers.back()->setY(y);
		createdTowers.push_back(availableTowers.back());
		availableTowers.pop_back();
		return true;
	}
	return false;
}

bool GameState::addTower()
{
	if (availableTowers.size() != 0) {
		float x = (float)tileX;
		float y = (float)tileY;
		getRealPos(x, y);
		// Check that no other towers are in this spot
		for (Tower* t : createdTowers) {
			if (t->getX() == x && t->getY() == y) {
				// TODO
				// If we found then [MESSAGE] OR [ANOTHER TILE COLOR] + return
				return false;
			}
		}
		availableTowers.back()->setX(x);
		availableTowers.back()->setY(y);
		createdTowers.push_back(availableTowers.back());
		availableTowers.pop_back();
		return true;
	}
	return false;
}

void GameState::removeTower(float x, float y)
{
	if (createdTowers.size() != 0) {
		getRealPos(x, y);
		unsigned short i = 0;
		for (Tower* t : createdTowers) {
			if (t->getX() == x && t->getY() == y) {
				Tower* erased = createdTowers[i];
				createdTowers.erase(createdTowers.begin() + i);
				delete erased;
				printf("Removed Tower at Pos %f,%f \n", x, y);
			}
			i++;
		}
	}
}

void GameState::removeTower()
{
	if (createdTowers.size() != 0) {
		float x = (float)tileX;
		float y = (float)tileY;
		getRealPos(x, y);
		unsigned short i = 0;
		for (Tower* t : createdTowers) {
			if (t->getX() == x && t->getY() == y) {
				Tower* erased = createdTowers[i];
				createdTowers.erase(createdTowers.begin() + i);
				delete erased;
				printf("Removed Tower at Pos %f,%f \n", x, y);
			}
			i++;
		}
	}
}

bool GameState::rearrangeTower(float x, float y)
{
	if (createdTowers.size() != 0) {
		getRealPos(x, y);
		unsigned short i = 0;
		for (Tower* t : createdTowers) {
			if (t->getX() == x && t->getY() == y) {
				Tower* erased = createdTowers[i];
				createdTowers.erase(createdTowers.begin() + i);
				availableTowers.push_back(erased);
				printf("Moved Tower from Pos %f,%f to available Towers \n", x, y);
				return true;
			}
			i++;
		}
	}
	return false;
}

bool GameState::rearrangeTower()
{
	if (createdTowers.size() != 0) {
		float x = (float)tileX;
		float y = (float)tileY;
		getRealPos(x, y);
		unsigned short i = 0;
		for (Tower* t : createdTowers) {
			if (t->getX() == x && t->getY() == y) {
				Tower* erased = createdTowers[i];
				createdTowers.erase(createdTowers.begin() + i);
				availableTowers.push_back(erased);
				printf("Moved Tower from Pos %f,%f to available Towers \n", x, y);
				return true;
			}
			i++;
		}
	}
	return false;
}

bool GameState::upgradeTower(float x, float y)
{
	if (createdTowers.size() != 0) {
		getRealPos(x, y);
		unsigned short i = 0;
		for (Tower* t : createdTowers) {
			if (t->getX() == x && t->getY() == y) {
				Tower* selected = createdTowers[i];
				int level = selected->getLevel();
				if (level < 3) {
					selected->setLevel(level + 1);
					printf("Upgraded Tower from Pos %f,%f to level %d \n", x, y, level+1);
					return true;
				}
			}
			i++;
		}
	}
	return false;
}

bool GameState::upgradeTower()
{
	if (createdTowers.size() != 0) {
		float x = (float)tileX;
		float y = (float)tileY;
		getRealPos(x, y);
		unsigned short i = 0;
		for (Tower* t : createdTowers) {
			if (t->getX() == x && t->getY() == y) {
				Tower* selected = createdTowers[i];
				int level = selected->getLevel();
				if (level < 3) {
					level += 1;
					selected->setLevel(level);
					if (level == 2) {
						selected->setFireRate(800);
						selected->setDamage(10);
						selected->setRange(3);
						selected->setTower(new GeometryNode());
						selected->getTower()->Init(towerLevelTwoMesh);
					}
					else {
						selected->setFireRate(700);
						selected->setDamage(15);
						selected->setRange(3);
						selected->setTower(new GeometryNode());
						selected->getTower()->Init(towerLevelThreeMesh);
					}
					printf("Upgraded Tower from Pos %f,%f to level %d \n", x, y, level);
					return true;
				}
			}
			i++;
		}
	}
	return false;
}

void GameState::getRealPos(float & x, float & y)
{
	x = 9 - x * 2;
	y = 9 - y * 2;
}

void GameState::getGridPos(float & x, float & y)
{
	x = (9 - x) / 2;
	y = (9 - y) / 2;
}

void GameState::setTilePosition(int x, int y)
{
	this->tileX = x;
	this->tileY = y;
}

void GameState::setTileX(int x)
{
	this->tileX = x;
}

void GameState::setTileY(int y)
{
	this->tileY = y;
}

int GameState::getTileX()
{
	return tileX;
}

int GameState::getTileY()
{
	return tileY;
}

void GameState::updateInRoad()
{
	for (auto t : road_tiles) {
		if (std::get<0>(t) == this->tileX && std::get<1>(t) == this->tileY) {
			inRoad = true;
			return;
		}
	}
	inRoad = false;
}

bool GameState::getInRoad()
{
	return inRoad;
}

bool GameState::isInRoad(int x, int y)
{
	for (auto t : road_tiles) {
		if (std::get<0>(t) == x && std::get<1>(t) == y) {
			return true;
		}
	}
	return false;
}

void GameState::setPirateBodyMesh(GeometricMesh * mesh)
{
	this->pirateBodyMesh = mesh;
}

void GameState::setPirateSwordMesh(GeometricMesh * mesh)
{
	this->pirateSwordMesh = mesh;
}

void GameState::setPirateLFootMesh(GeometricMesh * mesh)
{
	this->pirateLFootMesh = mesh;
}

void GameState::setPirateRFootMesh(GeometricMesh * mesh)
{
	this->pirateRFootMesh = mesh;
}

void GameState::assignMeshtoPirates()
{
	for (Pirate* p : pirates) {

		int type = p->getType();

		p->setBody(new GeometryNode());

		if(type == 1)
			p->getBody()->Init(pirateBodyMesh);
		else if(type == 0)
			p->getBody()->Init(pirateFastBodyMesh);
		else if(type == 2 || type == 3)
			p->getBody()->Init(pirateHeavyBodyMesh);

		p->setSword(new GeometryNode());
		if (type == 1)
			p->getBody()->Init(pirateSwordMesh);
		else if (type == 0)
			p->getBody()->Init(pirateFastSwordMesh);
		else if (type == 2 || type == 3)
			p->getBody()->Init(pirateHeavySwordMesh);

		p->setLeftFoot(new GeometryNode());
		if (type == 1)
			p->getBody()->Init(pirateLFootMesh);
		else if (type == 0)
			p->getBody()->Init(pirateFastLFootMesh);
		else if (type == 2 || type == 3)
			p->getBody()->Init(pirateHeavyLFootMesh);

		p->setRightFoot(new GeometryNode());
		if (type == 1)
			p->getBody()->Init(pirateRFootMesh);
		else if (type == 0)
			p->getBody()->Init(pirateFastRFootMesh);
		else if (type == 2 || type == 3)
			p->getBody()->Init(pirateHeavyRFootMesh);
	}
}

void GameState::setPirateFastBodyMesh(GeometricMesh * mesh)
{
	this->pirateFastBodyMesh = mesh;
}

void GameState::setPirateFastSwordMesh(GeometricMesh * mesh)
{
	this->pirateFastSwordMesh = mesh;
}

void GameState::setPirateFastLFootMesh(GeometricMesh * mesh)
{
	this->pirateFastLFootMesh = mesh;
}

void GameState::setPirateFastRFootMesh(GeometricMesh * mesh)
{
	this->pirateFastRFootMesh = mesh;
}

void GameState::setPirateHeavyBodyMesh(GeometricMesh * mesh)
{
	this->pirateHeavyBodyMesh = mesh;
}

void GameState::setPirateHeavySwordMesh(GeometricMesh * mesh)
{
	this->pirateHeavySwordMesh = mesh;
}

void GameState::setPirateHeavyLFootMesh(GeometricMesh * mesh)
{
	this->pirateHeavyLFootMesh = mesh;
}

void GameState::setPirateHeavyRFootMesh(GeometricMesh * mesh)
{
	this->pirateHeavyRFootMesh = mesh;
}

void GameState::createPirate(int pType, int pLevel)
{
	Pirate* p = new Pirate();

	p->setType(pType);
	p->setLevel(pLevel);

	int type = p->getType();

	// change stats according to type
	if (type == 0) {
		p->setSpeed(2.0f);
		p->setHealthPoints(70+5*pLevel);
		p->setStartHealth(70 + 5 * pLevel);
	}
	else if (type == 1) {
		p->setHealthPoints(100 + 10 * pLevel);
		p->setStartHealth(100 + 10 * pLevel);
	}
	else if (type == 2) {
		p->setSpeed(0.8f);
		p->setHealthPoints(250 + 15 * pLevel);
		p->setStartHealth(250 + 15 * pLevel);
	}
	else if (type == 3) {
		p->setSpeed(0.6f);
		p->setSize(1.5f);
		p->setHealthPoints(1500 + 25 * pLevel);
		p->setStartHealth(1500 + 25 * pLevel);
	}
	else if (type == 4) {
		p->setSpeed(1.0f);
		p->setSize(1.5f);
		p->setHealthPoints(1000 + 25 * pLevel);
		p->setStartHealth(1000 + 25 * pLevel);
	}

	p->setBody(new GeometryNode());

	if (type == 1)
		p->getBody()->Init(pirateBodyMesh);
	else if (type == 0)
		p->getBody()->Init(pirateFastBodyMesh);
	else if (type == 2 || type == 3)
		p->getBody()->Init(pirateHeavyBodyMesh);
	else if(type == 4)
		p->getBody()->Init(DarthVaderBody);

	p->setSword(new GeometryNode());
	if (type == 1)
		p->getSword()->Init(pirateSwordMesh);
	else if (type == 0)
		p->getSword()->Init(pirateFastSwordMesh);
	else if (type == 2 || type == 3)
		p->getSword()->Init(pirateHeavySwordMesh);
	else if (type == 4)
		p->getSword()->Init(lightsaberArm);

	p->setLeftFoot(new GeometryNode());
	if (type == 1)
		p->getLeftFoot()->Init(pirateLFootMesh);
	else if (type == 0)
		p->getLeftFoot()->Init(pirateFastLFootMesh);
	else if (type == 2 || type == 3 || type == 4)
		p->getLeftFoot()->Init(pirateHeavyLFootMesh);

	p->setRightFoot(new GeometryNode());
	if (type == 1)
		p->getRightFoot()->Init(pirateRFootMesh);
	else if (type == 0)
		p->getRightFoot()->Init(pirateFastRFootMesh);
	else if (type == 2 || type == 3 || type == 4)
		p->getRightFoot()->Init(pirateHeavyRFootMesh);

	p->setHealthGreen(new GeometryNode());
	p->getHealthGreen()->Init(greenTileMesh);

	p->setHealthRed(new GeometryNode());
	p->getHealthRed()->Init(redTileMesh);

	// Default test -- random
	/*unsigned idx = rand() % 29;
	p->setX(std::get<0>(road_tiles[idx]));
	p->setY(std::get<1>(road_tiles[idx]));*/

	// Put him in the start
	p->setX(std::get<0>(road_tiles[0]));
	p->setY(std::get<1>(road_tiles[0]));

	pirates.push_back(p);

}

void GameState::shootCannonBall(Tower * tower, Pirate * pirate)
{
	CannonBall* cannonball = new CannonBall();
	cannonball->setCannonBall(new GeometryNode());
	cannonball->getCannonBall()->Init(cannonballMesh);

	cannonball->setX(-2 * tower->getX());
	cannonball->setY(3.f); // TODO: maybe change it
	cannonball->setZ(-2 * tower->getY());

	//cannonball->setTargetX(-2 * pirate->getX());
	//cannonball->setTargetY(0.5f); // TODO: maybe change it
	//cannonball->setTargetZ(-2 * pirate->getY());

	cannonball->setTargetPirate(pirate);

	cannonball->setDamage(tower->getDamage());

	if (tower->getLevel()==3) {

		float r = (float)rand() / RAND_MAX;
		if (r <= 0.5f) {
			cannonball->setSpeed(0.5f);
			cannonball->setDamage(tower->getDamage() * 2);
			cannonball->setFireBall(true);
		}
	}

	cannonballs.push_back(cannonball);

}

void GameState::updatePirateTargets()
{
	for (Pirate* p : pirates) {

		if (p->isDead()) continue;

		// Check if pirate has reached the prev target
		bool reached = false;
		if (abs(p->getX() - p->getTargetX()) < 0.2 && abs(p->getY() - p->getTargetY()) < 0.2) {
			int idx = p->getRoadIdx();
			p->setRoadIdx(idx + 1);
			
		}

		// Get in which index is in the road
		int idx = p->getRoadIdx();

		// Set the target to the next x,y coordinates using the road_tiles
		if (idx + 1 < 29) {
			float x_new = std::get<0>(road_tiles[idx + 1]);
			float y_new = std::get<1>(road_tiles[idx + 1]);

			p->setTargetX(x_new);
			p->setTargetY(y_new);
		}
		else {
			// Set index to 29 as an indicator that it finished -- TODO: or later as the chest coordinates
			p->setRoadIdx(29);
			float x_new = 6;
			float y_new = -1;

			p->setTargetX(x_new);
			p->setTargetY(y_new);
		}

	}
}

void GameState::deleteHitCannonBall(CannonBall * cannonball)
{
	cannonballs.erase(std::remove(cannonballs.begin(), cannonballs.end(), cannonball), cannonballs.end());
	delete cannonball;
	// add to rem list
	// If it is not contained in the vector
	/*if (std::find(toRemCannonBalls.begin(), toRemCannonBalls.end(), cannonball) == toRemCannonBalls.end()) {
		toRemCannonBalls.push_back(cannonball);
	}*/
}

void GameState::deleteHitCannonBalls()
{
	unsigned int i = 0;
	for (CannonBall* cb : cannonballs) {
		if (cb->hasHitTarget()) {
			cannonballs.erase(cannonballs.begin() + i);
		}
		i += 1;
	}
}

void GameState::towersFire()
{
	for (Tower* t : createdTowers) {
		int state = t->getState();
		if (state == t->getFireRate()/100) {

			// Search for pirates inside the radius of the tower
			for (Pirate* p : pirates) {
				if (p->isDead()) continue;
				float tx = t->getX();
				float ty = t->getY();
				getGridPos(tx,ty);
				float px = p->getX();
				float py = p->getY();
				// Range of tower as tiles
				if (abs(tx - px) <= t->getRange() && abs(ty - py) <= t->getRange()) {
					float r = ((float)rand() / (RAND_MAX));
					if (r<=0.3f) getMusicManager()->PlaySFX("mortar.wav", 0, 0, 4);
					else if(r <= 0.6) getMusicManager()->PlaySFX("mortar.wav", 0, 0, 5);
					else getMusicManager()->PlaySFX("mortar.wav", 0, 0, 6);
					shootCannonBall(t, p);
					break;
				}
			}

			t->setState(0);
		}
		else {
			t->setState((state + 1) % (t->getFireRate() / 100 + 1));
		}
	}
}

void GameState::deletePirate(Pirate* pirate)
{
	pirates.erase(std::remove(pirates.begin(), pirates.end(), pirate), pirates.end());
	delete pirate;
	// If it is not contained in the vector
	/*if (std::find(toRemPirates.begin(), toRemPirates.end(), pirate) == toRemPirates.end()) {
		toRemPirates.push_back(pirate);
	}*/
}

void GameState::checkPiratesAtChest()
{
	for (Pirate* p : pirates) {
		if (p->isDead()) continue;
		if (p->getBoundingSphere()->isSphereIntersecting(treasureChest->getBoundingSphere())) {
			// Pirate reached gold..if it is the boss game over
			showGoldParticles = true;
			int type = p->getType();
			pirates.erase(std::remove(pirates.begin(), pirates.end(), p), pirates.end());
			if (type == 3 || type==4) {
				printf("GAME OVER\n");
				printf("Score: %d", score);
				gameOver = true;
			}else {
				gold -= 10;
				getMusicManager()->PlaySFX("coin_fall.wav",3 ,0, 1);
				// Check for gameover
				if (gold == 0) {
					// Game Over
					printf("GAME OVER\n");
					printf("Score: %d", score);
					gameOver = true;
				}
			}
		}
	}
}

void GameState::checkDeadPirates()
{
	for (Pirate* p : pirates) {
		if (p->isDead()) {
			int cycle = p->getDeadCycle();
			if (cycle <= 0) {
				deletePirate(p);
			}
			else {
				p->setDeadCycle(cycle - 1);
			}
		}
	}
	if (pirates.empty()) musicManager->QuitSFX(0);
}

void GameState::deleteToRemoveLists()
{
	for (Pirate* p : toRemPirates) {
		toRemPirates.erase(std::remove(toRemPirates.begin(), toRemPirates.end(), p), toRemPirates.end());
		delete p;
	}

	for (CannonBall* c : toRemCannonBalls) {
		toRemCannonBalls.erase(std::remove(toRemCannonBalls.begin(), toRemCannonBalls.end(), c), toRemCannonBalls.end());
		delete c;
	}
}

void GameState::checkCollidingPirates()
{
	for (Pirate* p : pirates) {
		if (p->isDead()) continue;
		//bool p_collides = false;
		for (Pirate* p2 : pirates) {
			if (p2->isDead()) continue;
			if (p != p2 && p->getBoundingSphere()->isSphereIntersecting(p2->getBoundingSphere())) {
				//p_collides = true;
				//printf("Pirate collide!\n");

				if (p->getSpeed() > p2->getSpeed()) {

					switch (p->getDir()) {
					case 0:
						// Up
						if(p->getY() < p2->getY()) p->setSpeed(p2->getSpeed());
						break;
					case 1:
						// Down
						if (p->getY() > p2->getY()) p->setSpeed(p2->getSpeed());
						break;
					case 2:
						// Left
						if (p->getX() < p2->getX()) p->setSpeed(p2->getSpeed());
						break;
					case 3:
						// Right
						if (p->getX() > p2->getX()) p->setSpeed(p2->getSpeed());
						break;

					}
					//p->setSpeed(p2->getSpeed());
				}
				else if (p2->getSpeed() > p->getSpeed()) {

					switch (p2->getDir()) {
					case 0:
						// Up
						if (p2->getY() < p->getY()) p2->setSpeed(p->getSpeed());
						break;
					case 1:
						// Down
						if (p2->getY() > p->getY()) p2->setSpeed(p->getSpeed());
						break;
					case 2:
						// Left
						if (p2->getX() < p->getX()) p2->setSpeed(p->getSpeed());
						break;
					case 3:
						// Right
						if (p2->getX() > p->getX()) p2->setSpeed(p->getSpeed());
						break;

					}
					//p2->setSpeed(p->getSpeed());
				}

				//switch (p->getDir()) {
				//case 0:
				//	// Up
				//	if (p->getY() > p2->getY()) {
				//		//p->setX(p->getX() - 0.2f);
				//		//p->setTargetX(p->getTargetX() - 0.5f);
				//		//p2->setX(p2->getX() + 0.2f);
				//		//p2->setTargetX(p2->getTargetX() + 0.5f);

				//		p2->setSpeed(p->getSpeed());
				//		p2->setY(p2->getY() - 0.01f);
				//	}
				//	break;
				//case 1:
				//	// Down
				//	if (p->getY() < p2->getY()) {
				//		//p->setX(p->getX() + 0.2f);
				//		//p->setTargetX(p->getTargetX() + 0.5f);
				//		//p2->setX(p2->getX() - 0.2f);
				//		//p2->setTargetX(p2->getTargetX() - 0.5f);
				//		p->setSpeed(p2->getSpeed());
				//		p2->setY(p2->getY() + 0.01f);
				//	}
				//	break;
				//case 2:
				//	// Left
				//	if (p->getX() > p2->getX()) {
				//		//p->setY(p->getY() + 0.2f);
				//		//p->setTargetY(p->getTargetY() + 0.5f);
				//		//p2->setY(p2->getY() - 0.2f);
				//		//p2->setTargetY(p2->getTargetY() - 0.5f);
				//		p2->setSpeed(p->getSpeed());
				//		p2->setX(p2->getX() + 0.01f);
				//	}
				//	break;
				//case 3:
				//	// Right
				//	if (p->getX() < p2->getX()) {
				//		//p->setY(p->getY() - 0.2f);
				//		//p->setTargetY(p->getTargetY() - 0.5f);
				//		//p2->setTargetY(p2->getTargetY() + 0.2f);
				//		//p2->setTargetY(p2->getTargetY() + 0.5f);
				//		p->setSpeed(p2->getSpeed());
				//		p2->setX(p2->getX() - 0.01f);
				//	}
				//	break;
				//case -1:
				//	// Unknown Angle
				//	break;
				//}
				
			
			}
		}
		/*if (!p_collides) {
			int type = p->getType();
			switch (type) {
			case 0:
				p->setSpeed(2);
				break;
			case 1:
				p->setSpeed(1);
				break;
			case 2:
				p->setSpeed(0.8f);
				break;
			case 3:
				p->setSpeed(0.6f);
				break;
			}
		}*/
	}
}

void GameState::resetPirateSpeeds()
{
	for (Pirate* p : pirates) {
		if (p->isDead()) continue;
		int type = p->getType();
		switch (type) {
		case 0:
			p->setSpeed(2);
			break;
		case 1:
			p->setSpeed(1);
			break;
		case 2:
			p->setSpeed(0.8f);
			break;
		case 3:
			p->setSpeed(0.6f);
			break;
		}
	}
}

bool GameState::getStopWaves()
{
	return stopWaves;
}

void GameState::setStopWaves(bool state)
{
	stopWaves = state;
}

bool GameState::getShowGoldParticles()
{
	return showGoldParticles;
}

void GameState::setShowGoldParticles(bool state)
{
	showGoldParticles = state;
}

void GameState::setTowerMesh(GeometricMesh * mesh)
{
	this->towerMesh = mesh;
}

void GameState::setTowerLevelTwoMesh(GeometricMesh * mesh)
{
	this->towerLevelTwoMesh = mesh;
}

void GameState::setTowerLevelThreeMesh(GeometricMesh * mesh)
{
	this->towerLevelThreeMesh = mesh;
}

void GameState::assignMeshToTowers()
{
	for (Tower* t : availableTowers) {
		t->setTower(new GeometryNode());
		t->getTower()->Init(towerMesh);
	}
}

void GameState::setCannonballMesh(GeometricMesh * mesh)
{
	cannonballMesh = mesh;
}

void GameState::setTreasureChestMesh(GeometricMesh * mesh)
{
	this->treasureChestMesh = mesh;
}

void GameState::assignTreasureChest()
{
	treasureChest->setChest(new GeometryNode());
	treasureChest->getChest()->Init(treasureChestMesh);
}

void GameState::setLightSaberArm(GeometricMesh * mesh)
{
	lightsaberArm = mesh;
}

void GameState::setDarthVaderBody(GeometricMesh * mesh)
{
	DarthVaderBody = mesh;
}

void GameState::setGreenTileMesh(GeometricMesh* mesh)
{
	greenTileMesh = mesh;
}

GeometricMesh * GameState::getGreenTileMesh()
{
	return greenTileMesh;
}

void GameState::setRedTileMesh(GeometricMesh * mesh)
{
	redTileMesh = mesh;
}

GeometricMesh * GameState::getRedTileMesh()
{
	return redTileMesh;
}

void GameState::createTower()
{
	Tower* t = new Tower();

	t->setTower(new GeometryNode());
	t->getTower()->Init(towerMesh);

	availableTowers.push_back(t);
}

MusicManager* GameState::getMusicManager() {
	return musicManager;
}

void GameState::setBoss(bool boss) {
	this->boss = boss;
}

bool GameState::getBoss() {
	return boss;
}

void GameState::setDarth(bool darth) {
	isDarth = darth;
}

bool GameState::getDarth() {
	return isDarth;
}

void GameState::setWasDarth(bool state)
{
	wasDarth = state;
}

bool GameState::getWasDarth()
{
	return wasDarth;
}

