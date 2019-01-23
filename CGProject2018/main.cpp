#include "SDL2/SDL.h"
#include <iostream>
#include <chrono>
#include "GLEW\glew.h"
#include "Renderer.h"
#include "GameState.h"

using namespace std;

//Screen attributes
SDL_Window * window;

//OpenGL context 
SDL_GLContext gContext;
const int SCREEN_WIDTH = 1380;	//800;	//640;
const int SCREEN_HEIGHT = 1024;	//600;	//480;

//Event handler
SDL_Event event;

Renderer * renderer = nullptr;

void func()
{
	system("pause");
}

// initialize SDL and OpenGL
bool init(GameState* game)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	// use Double Buffering
	if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0)
		std::cout << "Error: No double buffering" << endl;

	// set OpenGL Version (3.3)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Create Window
	window = SDL_CreateWindow("OpenGL Tower Defense Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (window == NULL)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return false;
	}

	//Create OpenGL context
	gContext = SDL_GL_CreateContext(window);
	if (gContext == NULL)
	{
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Disable Vsync
	if (SDL_GL_SetSwapInterval(0) == -1)
		printf("Warning: Unable to disable VSync! SDL Error: %s\n", SDL_GetError());

	// Initialize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("Error loading GLEW\n");
		return false;
	}
	// some versions of glew may cause an opengl error in initialization
	glGetError();

	renderer = new Renderer();

	// set renderer's game state

	renderer->setGameState(game);

	bool engine_initialized = renderer->Init(SCREEN_WIDTH, SCREEN_HEIGHT);

	//atexit(func);
	
	return engine_initialized;
}


void clean_up()
{
	delete renderer;

	SDL_GL_DeleteContext(gContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	// Initialize the Game State
	GameState* game = new GameState();

	//Initialize
	if (init(game) == false)
	{
		system("pause");
		return EXIT_FAILURE;
	}

	//Quit flag
	bool quit = false;
	bool mouse_button_pressed = false;
	glm::vec2 prev_mouse_position(0);

	auto simulation_start = chrono::steady_clock::now();

	//// Initialize position of tile to center of the map
	//int tileX, tileY;
	//tileX = 4;
	//tileY = 4;
	//renderer->TileSetPos(tileX, tileY);

	// Timers for timed events
	unsigned int lastTimeT1 = 0, lastTimeT2 = 0, lastTimeT3 = 0, lastTimeT4 = 0, lastTimeT5 = 0, lastTimeT6 = 0 ,currentTime, timePaused, timeRender=0, prevTimeRender=0;
	bool paused = false;
	bool wasPaused = false;

	//unsigned int piratesInWave = 0;

	struct wave {
		int num_of_pirates;
		std::vector<int> types;
		std::vector<int> levels;
	};

	wave piratesInWave;


	// Wait for user exit
	while (quit == false)
	{

		/*
		// NOT SURE IF HELPS

		lastTimeT1 += prevTimeRender>500?prevTimeRender:0;
		lastTimeT2 += prevTimeRender > 500 ? prevTimeRender : 0;
		lastTimeT3 += prevTimeRender > 500 ? prevTimeRender : 0;
		lastTimeT4 += prevTimeRender > 500 ? prevTimeRender : 0;
		lastTimeT5 += prevTimeRender > 500 ? prevTimeRender : 0;
		lastTimeT6 += prevTimeRender > 500 ? prevTimeRender : 0;*/

		timeRender = SDL_GetTicks();

		if (game->getGameOver()) {
			// If game over then pause the game
			paused = true;
		}

		// While there are events to handle
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				// Key down events
				if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;
				else if (event.key.keysym.sym == SDLK_k) renderer->ReloadShaders();
				else if (event.key.keysym.sym == SDLK_i) renderer->SetRenderingMode(Renderer::RENDERING_MODE::TRIANGLES);
				else if (event.key.keysym.sym == SDLK_o) renderer->SetRenderingMode(Renderer::RENDERING_MODE::LINES);
				else if (event.key.keysym.sym == SDLK_p) renderer->SetRenderingMode(Renderer::RENDERING_MODE::POINTS);
				else if (event.key.keysym.sym == SDLK_t)
				{
					bool inroad = game->getInRoad();
					if (!inroad) {
						game->addTower();
					}

				}
				else if (event.key.keysym.sym == SDLK_r)
				{
					bool inroad = game->getInRoad();
					if (!inroad) {
						game->rearrangeTower();
					}
				}
				else if (event.key.keysym.sym == SDLK_w)
				{
					renderer->CameraMoveForward(true);
				}
				else if (event.key.keysym.sym == SDLK_s)
				{
					renderer->CameraMoveBackWard(true);
				}
				else if (event.key.keysym.sym == SDLK_a)
				{
					renderer->CameraMoveLeft(true);
				}
				else if (event.key.keysym.sym == SDLK_d)
				{
					renderer->CameraMoveRight(true);
				}
				else if (event.key.keysym.sym == SDLK_UP && game->getTileY() + 1 <= 9)
				{
					game->setTileY(game->getTileY() + 1);
					game->updateInRoad();
				}
				else if (event.key.keysym.sym == SDLK_DOWN && game->getTileY() - 1 >= 0)
				{
					game->setTileY(game->getTileY() - 1);
					game->updateInRoad();
				}
				else if (event.key.keysym.sym == SDLK_LEFT && game->getTileX() + 1 <= 9)
				{
					game->setTileX(game->getTileX() + 1);
					game->updateInRoad();
				}
				else if (event.key.keysym.sym == SDLK_RIGHT && game->getTileX() - 1 >= 0)
				{
					game->setTileX(game->getTileX() - 1);
					game->updateInRoad();
				}
				else if (event.key.keysym.sym == SDLK_q)
				{
					// TEST TO CREATE PIRATE ON THE FLY
					//game->createPirate();
					/*if(game->getCreatedTowers().size() != 0)
						game->shootCannonBall(game->getCreatedTowers()[0], game->getPirates()[0]);*/

					// Create wave
					piratesInWave.num_of_pirates = 5;
					for (int i = 0; i < 5; i++) {
						piratesInWave.types.push_back(1);
						piratesInWave.levels.push_back(1);
					}

				}
				else if (event.key.keysym.sym == SDLK_0)
				{
					// Pause the game
					paused = !paused;
				}
				else if (event.key.keysym.sym == SDLK_u)
				{
					// Upgrade Tower
					game->upgradeTower();
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_w)
				{
					renderer->CameraMoveForward(false);
				}
				else if (event.key.keysym.sym == SDLK_s)
				{
					renderer->CameraMoveBackWard(false);
				}
				else if (event.key.keysym.sym == SDLK_a)
				{
					renderer->CameraMoveLeft(false);
				}
				else if (event.key.keysym.sym == SDLK_d)
				{
					renderer->CameraMoveRight(false);
				}
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				int x = event.motion.x;
				int y = event.motion.y;

				if (mouse_button_pressed)
				{
					renderer->CameraLook(glm::vec2(x, y) - prev_mouse_position);
					prev_mouse_position = glm::vec2(x, y);
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					int x = event.button.x;
					int y = event.button.y;
					mouse_button_pressed = (event.type == SDL_MOUSEBUTTONDOWN);
					prev_mouse_position = glm::vec2(x, y);
				}
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{
				int x = event.wheel.x;
				int y = event.wheel.y;
			}
			else if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					renderer->ResizeBuffers(event.window.data1, event.window.data2);
				}
			}
		}


		if(!paused){

			if (wasPaused) {
				timePaused = SDL_GetTicks() - timePaused;
				lastTimeT1 += timePaused;
				lastTimeT2 += timePaused;
				lastTimeT3 += timePaused;
				lastTimeT4 += timePaused;
				lastTimeT5 += timePaused;
				lastTimeT6 += timePaused;
			}
			else {
				timePaused = 0;
			}

			// Compute the ellapsed time
			auto simulation_end = chrono::steady_clock::now();
			float dt = chrono::duration <float>(simulation_end - simulation_start).count(); // in seconds
			simulation_start = chrono::steady_clock::now();

			// Create a timed event
			currentTime = SDL_GetTicks();
			if (currentTime > lastTimeT1 + 30 * 1000) {
				printf("Timed Event: 30 seconds have passed, one more Tower is available.\n");
				game->createTower();
				lastTimeT1 = currentTime;
			}

			// every 100ms
			currentTime = SDL_GetTicks();
			printf("CurrentTime: %d\nLastTimeT2: %d\n", currentTime, lastTimeT2);
			if (currentTime > lastTimeT2 + 100) {
				game->towersFire();
				lastTimeT2 = currentTime;
			}

			// every 10ms
			currentTime = SDL_GetTicks();
			if (currentTime > lastTimeT3 + 10) {
				//printf("Timed Event: 10ms - Updated Pirate Targets\n");
				game->updatePirateTargets();
				game->checkCollidingPirates();
				lastTimeT3 = currentTime;
			}

			//// every 10ms
			//currentTime = SDL_GetTicks();
			//if (currentTime > lastTimeT4 + 10) {
			//	game->deleteHitCannonBalls();
			//	lastTimeT4 = currentTime;
			//}

			// every 100ms
			currentTime = SDL_GetTicks();
			if (currentTime > lastTimeT4 + 500) {
				if (game->getShowGoldParticles()) game->setShowGoldParticles(false);
				game->checkPiratesAtChest();
				lastTimeT4 = currentTime;
			}

			// Create Waves
			currentTime = SDL_GetTicks();
			// if it is the first wave wait for 5 secs not 20
			if (game->getPirateWave() == 1) {
				if (currentTime > lastTimeT6 + 5000) {
					printf("THE WAVE IS: %d\n", game->getPirateWave());
					piratesInWave.num_of_pirates = 4;
					piratesInWave.types.clear();
					piratesInWave.levels.clear();
					for (int i = 0; i < piratesInWave.num_of_pirates; i++) {
						piratesInWave.types.push_back(1);
						piratesInWave.levels.push_back(1);
					}
					// testing only TODO:REMOVE
					//piratesInWave.types[2] = 0;
					//piratesInWave.types[1] = 0;
					//
					lastTimeT6 = currentTime;
					game->setPirateWave(game->getPirateWave() + 1);
				}
			}else if (game->getPirateWave() % 6 == 0){
				if (currentTime > lastTimeT6 + 20000) {
					printf("THE WAVE IS: %d\n", game->getPirateWave());
					// Every 6 waves spawn the boss!!
					piratesInWave.num_of_pirates = 1;
					piratesInWave.types.clear();
					piratesInWave.levels.clear();
					piratesInWave.types.push_back(3);
					piratesInWave.levels.push_back(1 + rand() % game->getPirateWave());
					lastTimeT6 = currentTime;
					game->setPirateWave(game->getPirateWave() + 1);
					game->setStopWaves(true);
				}
			}else {
				if (currentTime > lastTimeT6 + 20000 && !game->getStopWaves()) {
					printf("THE WAVE IS: %d\n", game->getPirateWave());
					piratesInWave.num_of_pirates = (game->getPirateWave() * 2 > 10) ? 10 : (game->getPirateWave() * 2);
					piratesInWave.types.clear();
					piratesInWave.levels.clear();
					for (int i = 0; i < piratesInWave.num_of_pirates; i++) {
						piratesInWave.types.push_back(rand() % 3);
						piratesInWave.levels.push_back(1 + rand() % game->getPirateWave());
					}
					std::sort(piratesInWave.types.begin(), piratesInWave.types.end(), std::greater<int>());
					lastTimeT6 = currentTime;
					game->setPirateWave(game->getPirateWave() + 1);
				}
			}
			
			// Create Pirate
			currentTime = SDL_GetTicks();
			if (currentTime > lastTimeT5 + game->getPirateRate()) {
				if (piratesInWave.num_of_pirates > 0) {
					piratesInWave.num_of_pirates -= 1;
					int type = piratesInWave.types[piratesInWave.num_of_pirates];
					int level = piratesInWave.levels[piratesInWave.num_of_pirates];
					game->createPirate(type, level);
					// Change rate that pirates are placed according to their type
					// in order to avoid collisions
					switch (type) {
					case 0:
						game->setPirateRate(1000);
						break;
					case 1:
						game->setPirateRate(2000);
						break;
					case 2:
						game->setPirateRate(3000);
						break;
					case 3:
						game->setPirateRate(2000);
						break;
					}
					lastTimeT5 = currentTime;
				}
			}

			// Update
			renderer->Update(dt, prevTimeRender);

			wasPaused = false;
		}
		else {
			// pause
			if (!wasPaused) {
				timePaused = SDL_GetTicks();
			}
			wasPaused = true;
		}

		// Draw
		renderer->Render();

		//Update screen (swap buffer for double buffering)
		SDL_GL_SwapWindow(window);

		timeRender = SDL_GetTicks() - timeRender;
		prevTimeRender = timeRender;
		// Print FPS
		//int fps = 0;
		//if (timeRender != 0) fps = 1000 / timeRender;

		//printf("FPS: %d\n", fps);
	}

	// Delete the game state
	delete game;

	//Clean up
	clean_up();

	return 0;
}