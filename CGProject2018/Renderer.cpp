#include "Renderer.h"
#include "GeometryNode.h"
#include "Tools.h"
#include <algorithm>
#include "ShaderProgram.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "OBJLoader.h"
#include <iostream>

// RENDERER
Renderer::Renderer()
{
	m_vbo_fbo_vertices = 0;
	m_vao_fbo = 0;
	
	// TODO

	// Terrain
	m_geometric_object1 = nullptr;

	// Road tiles
	m_geometric_object2 = new GeometryNode*[29];
	for (int i = 0; i < 29; i++) { 
		m_geometric_object2[i] = nullptr;
	}

	// Treasure Chest
	m_geometric_object3 = nullptr;

	m_fbo = 0;
	m_fbo_texture = 0;

	// Green Tile
	m_geometric_object4 = nullptr;

	// Red Tile
	m_geometric_object5 = nullptr;

	//// Pirate
	//m_geometric_object6 = nullptr;

	//// Pirate Sword
	//m_geometric_object7 = nullptr;

	//// Pirate Left Leg
	//m_geometric_object8 = nullptr;

	//// Pirate Right Leg
	//m_geometric_object9 = nullptr;

	/*pirates = std::vector<Pirate*>();
	availableTowers = std::vector<Tower*>();
	createdTowers = std::vector<Tower*>();*/

	//
	m_rendering_mode = RENDERING_MODE::TRIANGLES;	
	m_continous_time = 0.0;

	// initialize the camera parameters
	m_camera_position = glm::vec3(0.720552, 18.1377, -11.3135);
	m_camera_target_position = glm::vec3(4.005, 12.634, -5.66336);
	m_camera_up_vector = glm::vec3(0, 1, 0);
	
}

Renderer::~Renderer()
{
	// delete g_buffer
	glDeleteTextures(1, &m_fbo_texture);
	glDeleteFramebuffers(1, &m_fbo);

	// delete common data
	glDeleteVertexArrays(1, &m_vao_fbo);
	glDeleteBuffers(1, &m_vbo_fbo_vertices);

	// TODO

	delete m_geometric_object1;

	for (int i = 0; i < 29; i++) {
		delete m_geometric_object2[i];
	}

	delete m_geometric_object2;

	delete m_geometric_object3;

	delete m_geometric_object4;

	delete m_geometric_object5;

	/*delete m_geometric_object6;

	delete m_geometric_object7;

	delete m_geometric_object8;

	delete m_geometric_object9;*/

	//// delete all pirates
	//for (Pirate* p : pirates) {
	//	delete p;
	//}

	/*if (availableTowers.size() != 0) {
		for (int i = 0; i < availableTowers.size(); i++) {
			delete availableTowers[i];
		}
	}
	
	if (createdTowers.size() != 0) {
		for (int i = 0; i < createdTowers.size(); i++) {
			delete createdTowers[i];
		}
	}*/

	/*for (Tower* t : availableTowers) {
		delete t;
	}
	
	for (Tower* t : createdTowers) {
		delete t;
	}*/
}

bool Renderer::Init(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	this->m_screen_width = SCREEN_WIDTH;
	this->m_screen_height = SCREEN_HEIGHT;

	//// Initialize road tiles
	//road_tiles[0] = std::tuple<int,int>(0, 0);
	//road_tiles[1] = std::tuple<int, int>(0, 1);
	//road_tiles[2] = std::tuple<int, int>(0, 2);
	//road_tiles[3] = std::tuple<int, int>(0, 3);
	//road_tiles[4] = std::tuple<int, int>(1, 3);
	//road_tiles[5] = std::tuple<int, int>(1, 4);
	//road_tiles[6] = std::tuple<int, int>(1, 5);
	//road_tiles[7] = std::tuple<int, int>(1, 6);
	//road_tiles[8] = std::tuple<int, int>(1, 7);
	//road_tiles[9] = std::tuple<int, int>(2, 7);
	//road_tiles[10] = std::tuple<int, int>(2, 8);
	//road_tiles[11] = std::tuple<int, int>(3, 8);
	//road_tiles[12] = std::tuple<int, int>(4, 8);
	//road_tiles[13] = std::tuple<int, int>(5, 8);
	//road_tiles[14] = std::tuple<int, int>(6, 8);
	//road_tiles[15] = std::tuple<int, int>(6, 7);
	//road_tiles[16] = std::tuple<int, int>(6, 6);
	//road_tiles[17] = std::tuple<int, int>(7, 6);
	//road_tiles[18] = std::tuple<int, int>(7, 5);
	//road_tiles[19] = std::tuple<int, int>(7, 4);
	//road_tiles[20] = std::tuple<int, int>(7, 3);
	//road_tiles[21] = std::tuple<int, int>(8, 3);
	//road_tiles[22] = std::tuple<int, int>(9, 3);
	//road_tiles[23] = std::tuple<int, int>(9, 2);
	//road_tiles[24] = std::tuple<int, int>(9, 1);
	//road_tiles[25] = std::tuple<int, int>(8, 1);
	//road_tiles[26] = std::tuple<int, int>(7, 1);
	//road_tiles[27] = std::tuple<int, int>(6, 1);
	//road_tiles[28] = std::tuple<int, int>(6, 0);

	//// Create a pirate at position 0,0
	//Pirate* p1 = new Pirate();
	//p1->setX(0);
	//p1->setY(0);
	//pirates.push_back(p1);

	//Pirate* p2 = new Pirate();
	//p2->setX(1);
	//p2->setY(1);
	//pirates.push_back(p2);

	// Initialize OpenGL functions

	//Set clear color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//This enables depth and stencil testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	// glClearDepth sets the value the depth buffer is set at, when we clear it

	// Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// open the viewport
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT); //we set up our viewport

	bool techniques_initialization = InitRenderingTechniques();
	bool buffers_initialization = InitDeferredShaderBuffers();
	bool items_initialization = InitCommonItems();
	bool lights_sources_initialization = InitLightSources();
	bool meshes_initialization = InitGeometricMeshes();

	//If there was any errors
	if (Tools::CheckGLError() != GL_NO_ERROR)
	{
		printf("Exiting with error at Renderer::Init\n");
		return false;
	}

	//If everything initialized
	return techniques_initialization && items_initialization && buffers_initialization && meshes_initialization && lights_sources_initialization;
}

void Renderer::Update(float dt)
{
	float movement_speed = 15.0f;
	// compute the direction of the camera
	glm::vec3 direction = glm::normalize(m_camera_target_position - m_camera_position);

	// move the camera towards the direction of the camera
	m_camera_position += m_camera_movement.x *  movement_speed * direction * dt;
	m_camera_target_position += m_camera_movement.x * movement_speed * direction * dt;

	// move the camera sideways
	glm::vec3 right = glm::normalize(glm::cross(direction, m_camera_up_vector));
	m_camera_position += m_camera_movement.y *  movement_speed * right * dt;
	if (m_camera_position[1] < 0.5) m_camera_position[1] = 0.5;
	m_camera_target_position += m_camera_movement.y * movement_speed * right * dt;

	glm::mat4 rotation = glm::mat4(1.0f);
	float angular_speed = glm::pi<float>() * 0.0025f;
	
	// compute the rotation of the camera based on the mouse movement
	rotation *= glm::rotate(glm::mat4(1.0), m_camera_look_angle_destination.y * angular_speed, right);
	rotation *= glm::rotate(glm::mat4(1.0), -m_camera_look_angle_destination.x  * angular_speed, m_camera_up_vector);
	m_camera_look_angle_destination = glm::vec2(0);
	
	// rotate the camera direction
	direction = rotation * glm::vec4(direction, 0);
	float dist = glm::distance(m_camera_position, m_camera_target_position);
	m_camera_target_position = m_camera_position + direction * dist;

	// compute the view matrix
	m_view_matrix = glm::lookAt(m_camera_position, m_camera_target_position, m_camera_up_vector);

	m_continous_time += dt;

	// update meshes tranformations

	// TODO

	m_geometric_object1_transformation_matrix = glm::translate(glm::mat4(1.f), glm::vec3(18, 0, 18))*glm::scale(glm::mat4(1.f), glm::vec3(20.0f));
	m_geometric_object1_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object1_transformation_matrix))));

	m_geometric_object2_transformation_matrix = new glm::mat4[29];
	m_geometric_object2_transformation_normal_matrix = new glm::mat4[29];

	for (int i = 0; i < 29; i++) {

		float x = (float)std::get<0>(game->getRoadTiles()[i]);
		float y = (float)std::get<1>(game->getRoadTiles()[i]);

		game->getRealPos(x, y);

		m_geometric_object2_transformation_matrix[i] = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0.01f, -2 * y))*glm::translate(glm::mat4(1.f), glm::vec3(18, 0, 18))*glm::scale(glm::mat4(1.f), glm::vec3(2.0f));
		m_geometric_object2_transformation_normal_matrix[i] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object2_transformation_matrix[i]))));
	}

	m_geometric_object3_transformation_matrix = glm::translate(glm::mat4(1.f), glm::vec3(2 * 3.f, 0, -2 * 10.f))*glm::translate(glm::mat4(1.f), glm::vec3(18, 0, 18))* glm::scale(glm::mat4(1.0), glm::vec3(0.09f));
	m_geometric_object3_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object3_transformation_matrix))));

	float x = (float)game->getTileX();
	float y = (float)game->getTileY();

	game->getRealPos(x, y);

	bool inRoad = false;

	game->updateInRoad();

	inRoad = game->getInRoad();

	glm::mat4 terrainTransform = glm::translate(glm::mat4(1.f), glm::vec3(18, 0.05f, 18));

	if (!inRoad) {

		m_geometric_object4_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0.01f, -2 * y))* terrainTransform * glm::scale(glm::mat4(1.0), glm::vec3(2.0f));
		m_geometric_object4_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object4_transformation_matrix))));
	}else {
		m_geometric_object5_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0.01f, -2 * y))* terrainTransform * glm::scale(glm::mat4(1.0), glm::vec3(2.0f));
		m_geometric_object5_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object5_transformation_matrix))));
	}

	/*m_geometric_object10_transformation_matrix = new glm::mat4[createdTowers.size()];
	m_geometric_object10_transformation_normal_matrix = new glm::mat4[createdTowers.size()];
	if (createdTowers.size() != 0) {
		for (int i = 0; i < createdTowers.size(); i++) {
			m_geometric_object10_transformation_matrix[i] = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * createdTowers[i]->getX(), 0, -2 * createdTowers[i]->getY()))* terrainTransform * glm::scale(glm::mat4(1.0), glm::vec3(0.4f));
			m_geometric_object10_transformation_normal_matrix[i] = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object10_transformation_matrix[i]))));
		}
			
	}*/
	for (Tower* t : game->getCreatedTowers()) {
		x = t->getX();
		y = t->getY();

		glm::mat4 m_geometric_object10_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0, -2 * y))* terrainTransform * glm::scale(glm::mat4(1.0), glm::vec3(0.4f));
		glm::mat4 m_geometric_object10_transformation_normal_matrix= glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object10_transformation_matrix))));
		
		t->setTowerTM(m_geometric_object10_transformation_matrix);
		t->setTowerTNM(m_geometric_object10_transformation_normal_matrix);
	}

	// For Pirates

	for (Pirate* p : game->getPirates()) {
		x = p->getX();
		y = p->getY();

		game->getRealPos(x, y);

		// find the new location as the pirate follows the path
		float target_x = p->getTargetX();
		float target_y = p->getTargetY();

		game->getRealPos(target_x, target_y);


		//float x_new = x + (0.05 * (x < target_x) + (-0.05 *(x > target_x)));
		//float y_new = y + (0.05 * (y < target_y) + (-0.05 *(y > target_y)));

		auto deltaTargetX = target_x - x;
		auto deltaTargetY = target_y - y;

		float x_new = x + ((abs(deltaTargetX) < 0.15) ? 0 : (0.01*(deltaTargetX > 0) - 0.01*(deltaTargetX <= 0)));
		float y_new = y + ((abs(deltaTargetY) < 0.15) ? 0 : (0.01*(deltaTargetY > 0) - 0.01*(deltaTargetY <= 0)));

		/*float t = float(((int)m_continous_time % 5000))/5000;

		float x_new = x + (target_x - x) * t;
		float y_new = y + (target_y - y) * t;*/

		/*printf("X: %f, X2: %f\t", x, x_new);
		printf("Y: %f, Y2: %f\n", y, y_new);*/

		auto deltaX = x_new - x;
		auto deltaY = y_new - y;
		auto rad = atan2(deltaY, -deltaX);

		//printf("Rad: %f\n", rad);

		// special cases

		glm::mat4 pirateRot;

		if (p->getRoadIdx() == 1) pirateRot = glm::rotate(glm::mat4(1.0f), -glm::pi<float>(), glm::vec3(0, 1, 0));
		else if (p->getRoadIdx() == 29) {
			pirateRot = glm::rotate(glm::mat4(1.0f), 0.f, glm::vec3(0, 1, 0));
		}
		else {
			pirateRot = glm::rotate(glm::mat4(1.0f), rad - glm::pi<float>() / 2, glm::vec3(0, 1, 0));
		}
		x = x_new;
		y = y_new;

		game->getGridPos(x_new, y_new);


		p->setX(x_new);
		p->setY(y_new);

		// body

		glm::mat4 m_geometric_object6_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0.1f, -2 * y))* terrainTransform * pirateRot * glm::scale(glm::mat4(1.0), glm::vec3(0.09f));
		glm::mat4 m_geometric_object6_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object6_transformation_matrix))));

		p->setBodyTM(m_geometric_object6_transformation_matrix);
		p->setBodyTNM(m_geometric_object6_transformation_normal_matrix);

		//glm::mat4 pivotRot = glm::rotate(glm::mat4(1.0f), sin(m_continous_time)*(glm::pi<float>() / 4), glm::vec3(1, 0, 0));
		glm::mat4 pivotRot = glm::rotate(glm::mat4(1.0f), cos(5*m_continous_time+p->getAnimStart())*(glm::pi<float>() / 4), glm::vec3(1, 0, 0));
		glm::mat4 stPivotRot = glm::rotate(glm::mat4(1.0f), -(glm::pi<float>() / 4), glm::vec3(1, 0, 0));

		// sword

		glm::mat4 m_geometric_object7_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0.1f, -2 * y))* terrainTransform * pirateRot * glm::translate(glm::mat4(1.0f), glm::vec3(4.5*0.09, 9.5 * 0.09, 1 * 0.09))*
			glm::translate(glm::mat4(1.0f), glm::vec3(0, .3, 0))* pivotRot *glm::translate(glm::mat4(1.0f), glm::vec3(0, -.3, 0))* stPivotRot * glm::scale(glm::mat4(1.0), glm::vec3(0.09f));;
		glm::mat4 m_geometric_object7_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object7_transformation_matrix))));

		p->setSwordTM(m_geometric_object7_transformation_matrix);
		p->setSwordTNM(m_geometric_object7_transformation_normal_matrix);

		// left foot

		glm::mat4 animLFoot = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 2*0.09f+sin(10*m_continous_time + p->getAnimStart())* 2 * 0.09f));

		glm::mat4 m_geometric_object8_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0.1f, -2 * y))* terrainTransform * pirateRot * glm::translate(glm::mat4(1.0f), glm::vec3(-4 * 0.09, 0, -2 * 0.09)) * animLFoot *glm::scale(glm::mat4(1.0), glm::vec3(0.09f));;
		glm::mat4 m_geometric_object8_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object8_transformation_matrix))));

		p->setLeftFootTM(m_geometric_object8_transformation_matrix);
		p->setLeftFootTNM(m_geometric_object8_transformation_normal_matrix);

		// right foot

		glm::mat4 animRFoot = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2*0.09f-sin(10*m_continous_time + p->getAnimStart())*2 * 0.09f));

		glm::mat4 m_geometric_object9_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0.1f, -2 * y))* terrainTransform * pirateRot * glm::translate(glm::mat4(1.0f), glm::vec3(4 * 0.09, 0, 2 * 0.09)) * animRFoot * glm::scale(glm::mat4(1.0), glm::vec3(0.09f));;
		glm::mat4 m_geometric_object9_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object9_transformation_matrix))));
		
		p->setRightFootTM(m_geometric_object9_transformation_matrix);
		p->setRightFootTNM(m_geometric_object9_transformation_normal_matrix);

	}

	// For the CannonBalls
	for (CannonBall* cb : game->getCannonBalls()) {

		float x, y, z;
		x = cb->getX();
		y = cb->getY();
		z = cb->getZ();

		float tx, ty, tz;
		/*tx = cb->getTargetX();
		ty = cb->getTargetY();
		tz = cb->getTargetZ();*/

		Pirate* targetPirate = cb->getTargetPirate();

		tx = -18 + 4 * targetPirate->getX();
		ty = 0.5f;
		tz = -18 + 4 * targetPirate->getY();

		auto deltaTargetX = tx - x;
		auto deltaTargetY = ty - y;
		auto deltaTargetZ = tz - z;

		float x_new = x + ((abs(deltaTargetX) < 0.05) ? 0 : cb->getSpeed() * (0.2*(deltaTargetX > 0) - 0.2*(deltaTargetX <= 0)));
		float y_new = y + ((abs(deltaTargetY) < 0.005) ? 0 : cb->getSpeed() * (0.01*(deltaTargetY > 0) - 0.01*(deltaTargetY <= 0)));
		float z_new = z + ((abs(deltaTargetZ) < 0.05) ? 0 : cb->getSpeed() * (0.2*(deltaTargetZ > 0) - 0.2*(deltaTargetZ <= 0)));

		cb->setX(x_new);
		cb->setY(y_new);
		cb->setZ(z_new);

		if (cb->getBoundingSphere()->isSphereIntersecting(targetPirate->getBoundingSphere())) {
			std::cout << "BAM" << std::endl;
			game->deleteHitCannonBall(cb);
			targetPirate->setHealthPoints(targetPirate->getHealthPoints() - 10);
			if (targetPirate->getHealthPoints() == 0) {
				std::cout << "Pirate died!" << std::endl;
				game->deletePirate(targetPirate);
				// increase score
				game->setScore(game->getScore() + 1);
			}
			cb->setHitTarget(true);
		}

		glm::mat4 m_cannonball_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(cb->getX(), cb->getY(), cb->getZ()))* terrainTransform * glm::scale(glm::mat4(1.0), glm::vec3(0.09f));
		glm::mat4 m_cannonball_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_cannonball_transformation_matrix))));

		cb->setCannonBallTM(m_cannonball_transformation_matrix);
		cb->setCannonBallTNM(m_cannonball_transformation_normal_matrix);

	}

	//x = 0;
	//y = 0;

	//getRealPos(x, y);

	//glm::mat4 pirateRot = glm::rotate(glm::mat4(1.0f), -(glm::pi<float>()), glm::vec3(0, 1, 0));

	//m_geometric_object6_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0.1f, -2 * y))* terrainTransform * pirateRot * glm::scale(glm::mat4(1.0), glm::vec3(0.09f));
	//m_geometric_object6_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object6_transformation_matrix))));

	////glm::mat4 pivotRot = glm::rotate(glm::mat4(1.0f), sin(m_continous_time)*(glm::pi<float>() / 4), glm::vec3(1, 0, 0));
	//glm::mat4 pivotRot = glm::rotate(glm::mat4(1.0f), cos(m_continous_time)*(glm::pi<float>() / 4), glm::vec3(1, 0, 0));
	//glm::mat4 stPivotRot = glm::rotate(glm::mat4(1.0f), -(glm::pi<float>() / 4), glm::vec3(1, 0, 0));

	//m_geometric_object7_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0.1f, -2 * y))* terrainTransform * pirateRot * glm::translate(glm::mat4(1.0f), glm::vec3(4.5*0.09, 9.5 * 0.09, 1 * 0.09))*
	//	glm::translate(glm::mat4(1.0f), glm::vec3(0, .3, 0))* pivotRot *glm::translate(glm::mat4(1.0f), glm::vec3(0, -.3, 0))* stPivotRot * glm::scale(glm::mat4(1.0), glm::vec3(0.09f));;
	//m_geometric_object7_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object7_transformation_matrix))));

	//m_geometric_object8_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0.1f, -2 * y))* terrainTransform * pirateRot * glm::translate(glm::mat4(1.0f), glm::vec3(-4 * 0.09, 0, -2 * 0.09)) * glm::scale(glm::mat4(1.0), glm::vec3(0.09f));;
	//m_geometric_object8_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object8_transformation_matrix))));

	//m_geometric_object9_transformation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2 * x, 0.1f, -2 * y))* terrainTransform * pirateRot * glm::translate(glm::mat4(1.0f), glm::vec3(4 * 0.09, 0, 2 * 0.09)) * glm::scale(glm::mat4(1.0), glm::vec3(0.09f));;
	//m_geometric_object9_transformation_normal_matrix = glm::mat4(glm::transpose(glm::inverse(glm::mat3(m_geometric_object9_transformation_matrix))));

}

bool Renderer::InitCommonItems()
{
	glGenVertexArrays(1, &m_vao_fbo);
	glBindVertexArray(m_vao_fbo);

	GLfloat fbo_vertices[] = {
		-1, -1,
		1, -1,
		-1, 1,
		1, 1,
	};

	glGenBuffers(1, &m_vbo_fbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_fbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertices), fbo_vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);

	return true;
}

bool Renderer::InitRenderingTechniques()
{
	bool initialized = true;

	// Geometry Rendering Program
	std::string vertex_shader_path = "../Data/Shaders/basic_rendering.vert";
	std::string fragment_shader_path = "../Data/Shaders/basic_rendering.frag";
	m_geometry_rendering_program.LoadVertexShaderFromFile(vertex_shader_path.c_str());
	m_geometry_rendering_program.LoadFragmentShaderFromFile(fragment_shader_path.c_str());
	initialized = m_geometry_rendering_program.CreateProgram();
	m_geometry_rendering_program.LoadUniform("uniform_projection_matrix");
	m_geometry_rendering_program.LoadUniform("uniform_view_matrix");
	m_geometry_rendering_program.LoadUniform("uniform_model_matrix");
	m_geometry_rendering_program.LoadUniform("uniform_normal_matrix");
	m_geometry_rendering_program.LoadUniform("uniform_diffuse");
	m_geometry_rendering_program.LoadUniform("uniform_specular");
	m_geometry_rendering_program.LoadUniform("uniform_shininess");
	m_geometry_rendering_program.LoadUniform("uniform_has_texture");
	m_geometry_rendering_program.LoadUniform("diffuse_texture");
	m_geometry_rendering_program.LoadUniform("uniform_camera_position");
	// Light Source Uniforms
	m_geometry_rendering_program.LoadUniform("uniform_light_projection_matrix");
	m_geometry_rendering_program.LoadUniform("uniform_light_view_matrix");
	m_geometry_rendering_program.LoadUniform("uniform_light_position");
	m_geometry_rendering_program.LoadUniform("uniform_light_direction");
	m_geometry_rendering_program.LoadUniform("uniform_light_color");
	m_geometry_rendering_program.LoadUniform("uniform_light_umbra");
	m_geometry_rendering_program.LoadUniform("uniform_light_penumbra");
	m_geometry_rendering_program.LoadUniform("uniform_cast_shadows");
	m_geometry_rendering_program.LoadUniform("shadowmap_texture");

	// Post Processing Program
	vertex_shader_path = "../Data/Shaders/postproc.vert";
	fragment_shader_path = "../Data/Shaders/postproc.frag";
	m_postprocess_program.LoadVertexShaderFromFile(vertex_shader_path.c_str());
	m_postprocess_program.LoadFragmentShaderFromFile(fragment_shader_path.c_str());
	initialized = initialized && m_postprocess_program.CreateProgram();
	m_postprocess_program.LoadUniform("uniform_texture");
	m_postprocess_program.LoadUniform("uniform_time");
	m_postprocess_program.LoadUniform("uniform_depth");
	m_postprocess_program.LoadUniform("uniform_projection_inverse_matrix");

	// Shadow mapping Program
	vertex_shader_path = "../Data/Shaders/shadow_map_rendering.vert";
	fragment_shader_path = "../Data/Shaders/shadow_map_rendering.frag";
	m_spot_light_shadow_map_program.LoadVertexShaderFromFile(vertex_shader_path.c_str());
	m_spot_light_shadow_map_program.LoadFragmentShaderFromFile(fragment_shader_path.c_str());
	initialized = initialized && m_spot_light_shadow_map_program.CreateProgram();
	m_spot_light_shadow_map_program.LoadUniform("uniform_projection_matrix");
	m_spot_light_shadow_map_program.LoadUniform("uniform_view_matrix");
	m_spot_light_shadow_map_program.LoadUniform("uniform_model_matrix");
	
	return initialized;
}

bool Renderer::ReloadShaders()
{
	bool reloaded = true;

	reloaded = reloaded && m_geometry_rendering_program.ReloadProgram();
	reloaded = reloaded && m_postprocess_program.ReloadProgram();
	reloaded = reloaded && m_spot_light_shadow_map_program.ReloadProgram();

	return reloaded;
}

bool Renderer::InitDeferredShaderBuffers()
{
	// generate texture handles 
	glGenTextures(1, &m_fbo_texture);
	glGenTextures(1, &m_fbo_depth_texture);

	// framebuffer to link everything together
	glGenFramebuffers(1, &m_fbo);

	return ResizeBuffers(m_screen_width, m_screen_height);
}

// resize post processing textures and save the screen size
bool Renderer::ResizeBuffers(int width, int height)
{
	m_screen_width = width;
	m_screen_height = height;

	// texture
	glBindTexture(GL_TEXTURE_2D, m_fbo_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_screen_width, m_screen_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	// depth texture
	glBindTexture(GL_TEXTURE_2D, m_fbo_depth_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_screen_width, m_screen_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	// framebuffer to link to everything together
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_fbo_texture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_fbo_depth_texture, 0);

	GLenum status = Tools::CheckFramebufferStatus(m_fbo);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		return false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	m_projection_matrix = glm::perspective(glm::radians(60.f), width / (float)height, 0.1f, 1500.0f);
	m_view_matrix = glm::lookAt(m_camera_position, m_camera_target_position, m_camera_up_vector);

	return true;
}

// Initialize the light sources
bool Renderer::InitLightSources()
{
	// Initialize the spot light -- changed to pdf specifics
	m_spotlight_node.SetPosition(glm::vec3(16, 30, 16));
	m_spotlight_node.SetTarget(glm::vec3(16.4, 0, 16));
	//m_spotlight_node.SetTarget(glm::vec3(0, 0, 0));
	m_spotlight_node.SetColor(glm::vec3(140, 140, 140));
	m_spotlight_node.SetConeSize(73, 80);
	//m_spotlight_node.SetConeSize(100, 120);
	m_spotlight_node.CastShadow(true);

	return true;
}

// Load Geometric Meshes
// TODO
bool Renderer::InitGeometricMeshes()
{
	bool initialized = true;
	OBJLoader loader;
	// load geometric object 1
	auto mesh = loader.load("../Data/Terrain/terrain.obj");
	if (mesh != nullptr)
	{
		m_geometric_object1 = new GeometryNode();
		m_geometric_object1->Init(mesh);
	}
	else
		initialized = false;

	// load geometric object 2
	mesh = loader.load("../Data/Terrain/road.obj");
	if (mesh != nullptr)
	{
		for(int i=0;i<29;i++){
			m_geometric_object2[i] = new GeometryNode();
			m_geometric_object2[i]->Init(mesh);
		}
		
	}
	else
		initialized = false;

	// load geometric object 3
	mesh = loader.load("../Data/Treasure/treasure_chest.obj");
	if (mesh != nullptr)
	{
		m_geometric_object3 = new GeometryNode();
		m_geometric_object3->Init(mesh);
	}
	else
		initialized = false;

	// load geometric object 4
	mesh = loader.load("../Data/Various/plane_green.obj");
	if (mesh != nullptr)
	{
		m_geometric_object4 = new GeometryNode();
		m_geometric_object4->Init(mesh);
	}
	else
		initialized = false;

	// load geometric object 5
	mesh = loader.load("../Data/Various/plane_red.obj");
	if (mesh != nullptr)
	{
		m_geometric_object5 = new GeometryNode();
		m_geometric_object5->Init(mesh);
	}
	else
		initialized = false;

	//// load geometric object 6
	//mesh = loader.load("../Data/Pirate/pirate_body.obj");
	//if (mesh != nullptr)
	//{
	//	m_geometric_object6 = new GeometryNode();
	//	m_geometric_object6->Init(mesh);
	//}
	//else
	//	initialized = false;

	//// load geometric object 7
	//mesh = loader.load("../Data/Pirate/pirate_arm.obj");
	//if (mesh != nullptr)
	//{
	//	m_geometric_object7 = new GeometryNode();
	//	m_geometric_object7->Init(mesh);
	//}
	//else
	//	initialized = false;

	//// load geometric object 8
	//mesh = loader.load("../Data/Pirate/pirate_left_foot.obj");
	//if (mesh != nullptr)
	//{
	//	m_geometric_object8 = new GeometryNode();
	//	m_geometric_object8->Init(mesh);
	//}
	//else
	//	initialized = false;

	//// load geometric object 9
	//mesh = loader.load("../Data/Pirate/pirate_right_foot.obj");
	//if (mesh != nullptr)
	//{
	//	m_geometric_object9 = new GeometryNode();
	//	m_geometric_object9->Init(mesh);
	//}
	//else
	//	initialized = false;

	mesh = loader.load("../Data/Pirate/pirate_body.obj");
	if (mesh != nullptr) {
		game->setPirateBodyMesh(loader.load("../Data/Pirate/pirate_body.obj"));
	}
	else
		initialized = false;

	mesh = loader.load("../Data/Pirate/pirate_arm.obj");
	if (mesh != nullptr) {
		game->setPirateSwordMesh(loader.load("../Data/Pirate/pirate_arm.obj"));
	}
	else
		initialized = false;

	mesh = loader.load("../Data/Pirate/pirate_left_foot.obj");
	if (mesh != nullptr) {
		game->setPirateLFootMesh(loader.load("../Data/Pirate/pirate_left_foot.obj"));
	}
	else
		initialized = false;

	mesh = loader.load("../Data/Pirate/pirate_right_foot.obj");
	if (mesh != nullptr) {
		game->setPirateRFootMesh(loader.load("../Data/Pirate/pirate_right_foot.obj"));
	}
	else
		initialized = false;
	
	game->assignMeshtoPirates();

	/*for (Pirate* p : game->getPirates()) {
		p->setBody(new GeometryNode());
		p->getBody()->Init(mesh1);

		p->setSword(new GeometryNode());
		p->getSword()->Init(mesh2);

		p->setLeftFoot(new GeometryNode());
		p->getLeftFoot()->Init(mesh3);

		p->setRightFoot(new GeometryNode());
		p->getRightFoot()->Init(mesh4);

	}*/

	// load geometric object 10
	mesh = loader.load("../Data/MedievalTower/tower.obj");
	if (mesh != nullptr)
	{
		game->setTowerMesh(mesh);

		game->assignMeshToTowers();

		//// You start with 3 towers
		//for (int i = 0; i < 3; i++) {
		//	Tower* tower = new Tower();
		//	tower->setTower(new GeometryNode());
		//	tower->getTower()->Init(mesh);
		//	game->getAvailableTowers().push_back(tower);
		//}
	}
	else
		initialized = false;

	// load cannonball mesh
	mesh = loader.load("../Data/Various/cannonball.obj");
	if (mesh != nullptr) {
		game->setCannonballMesh(mesh);
	}
	else
		initialized = false;

	return initialized;
}

void Renderer::SetRenderingMode(RENDERING_MODE mode)
{
	m_rendering_mode = mode;
}

// Render the Scene
void Renderer::Render()
{
	
	// Draw the geometry to the shadow maps
	RenderShadowMaps();

	// Draw the geometry
	RenderGeometry();

	// Render to screen
	RenderToOutFB();

	GLenum error = Tools::CheckGLError();
	if (error != GL_NO_ERROR)
	{
		printf("Reanderer:Draw GL Error\n");
		system("pause");
	}
}

void Renderer::RenderShadowMaps()
{
	// if the light source casts shadows
	if (m_spotlight_node.GetCastShadowsStatus())
	{
		int m_depth_texture_resolution = m_spotlight_node.GetShadowMapResolution();

		// bind the framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, m_spotlight_node.GetShadowMapFBO());
		glViewport(0, 0, m_depth_texture_resolution, m_depth_texture_resolution);
		GLenum drawbuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, drawbuffers);
		
		// clear depth buffer
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		
		// Bind the shadow mapping program
		m_spot_light_shadow_map_program.Bind();

		// pass the projection and view matrix to the uniforms
		glUniformMatrix4fv(m_spot_light_shadow_map_program["uniform_projection_matrix"], 1, GL_FALSE, glm::value_ptr(m_spotlight_node.GetProjectionMatrix()));
		glUniformMatrix4fv(m_spot_light_shadow_map_program["uniform_view_matrix"], 1, GL_FALSE, glm::value_ptr(m_spotlight_node.GetViewMatrix()));

		// TODO

		// draw the first object
		DrawGeometryNodeToShadowMap(m_geometric_object1, m_geometric_object1_transformation_matrix, m_geometric_object1_transformation_normal_matrix);

		// draw the second object
		for (int i = 0; i < 29; i++) {
			DrawGeometryNodeToShadowMap(m_geometric_object2[i], m_geometric_object2_transformation_matrix[i], m_geometric_object2_transformation_normal_matrix[i]);
		}

		// draw the third object
		DrawGeometryNodeToShadowMap(m_geometric_object3, m_geometric_object3_transformation_matrix, m_geometric_object3_transformation_normal_matrix);
		
		// These don't need shadows

		//if (!inRoad) {
		//	// draw the fourth object
		//	DrawGeometryNodeToShadowMap(m_geometric_object4, m_geometric_object4_transformation_matrix, m_geometric_object4_transformation_normal_matrix);
		//}
		//else {
		//	// draw the fifth object
		//	DrawGeometryNodeToShadowMap(m_geometric_object5, m_geometric_object5_transformation_matrix, m_geometric_object5_transformation_normal_matrix);
		//}
		/*if (createdTowers.size() != 0) {
			for (int i = 0; i < createdTowers.size(); i++) {
				DrawGeometryNodeToShadowMap(createdTowers[i], m_geometric_object10_transformation_matrix[i], m_geometric_object10_transformation_normal_matrix[i]);
			}
		}*/
		for (Tower* t : game->getCreatedTowers()) {
			DrawGeometryNodeToShadowMap(t->getTower(), t->getTowerTM(), t->getTowerTNM());
		}



		//// draw the sixth object
		//DrawGeometryNodeToShadowMap(m_geometric_object6, m_geometric_object6_transformation_matrix, m_geometric_object6_transformation_normal_matrix);

		//// draw the 7th object
		//DrawGeometryNodeToShadowMap(m_geometric_object7, m_geometric_object7_transformation_matrix, m_geometric_object7_transformation_normal_matrix);

		//// draw the 8th object
		//DrawGeometryNodeToShadowMap(m_geometric_object8, m_geometric_object8_transformation_matrix, m_geometric_object8_transformation_normal_matrix);

		//// draw the 9th object
		//DrawGeometryNodeToShadowMap(m_geometric_object9, m_geometric_object9_transformation_matrix, m_geometric_object9_transformation_normal_matrix);

		for (Pirate* p : game->getPirates()) {
			// body
			DrawGeometryNodeToShadowMap(p->getBody(), p->getBodyTM(), p->getBodyTNM());

			// sword
			DrawGeometryNodeToShadowMap(p->getSword(), p->getSwordTM(), p->getSwordTNM());

			// leftfoot
			DrawGeometryNodeToShadowMap(p->getLeftFoot(), p->getLeftFootTM(), p->getLeftFootTNM());

			//rightfoot
			DrawGeometryNodeToShadowMap(p->getRightFoot(), p->getRightFootTM(), p->getRightFootTNM());

		}

		// draw the cannonballs
		for (CannonBall* cannonball : game->getCannonBalls()) {
			DrawGeometryNodeToShadowMap(cannonball->getCannonBall(), cannonball->getCannonBallTM(), cannonball->getCannonBallTNM());
		}

		glBindVertexArray(0);

		// Unbind shadow mapping program
		m_spot_light_shadow_map_program.Unbind();
		
		glDisable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}


void Renderer::RenderGeometry()
{
	// Bind the Intermediate framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glViewport(0, 0, m_screen_width, m_screen_height);
	GLenum drawbuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawbuffers);
	
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glEnable(GL_DEPTH_TEST);
	
	switch (m_rendering_mode)
	{
	case RENDERING_MODE::TRIANGLES:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case RENDERING_MODE::LINES:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case RENDERING_MODE::POINTS:
		glPointSize(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	};
	
	// Bind the geometry rendering program
	m_geometry_rendering_program.Bind();

	// pass camera parameters to uniforms
	glUniformMatrix4fv(m_geometry_rendering_program["uniform_projection_matrix"], 1, GL_FALSE, glm::value_ptr(m_projection_matrix));
	glUniformMatrix4fv(m_geometry_rendering_program["uniform_view_matrix"], 1, GL_FALSE, glm::value_ptr(m_view_matrix));
	glUniform3f(m_geometry_rendering_program["uniform_camera_position"], m_camera_position.x, m_camera_position.y, m_camera_position.z);
	
	// pass the light source parameters to uniforms
	glm::vec3 light_position = m_spotlight_node.GetPosition();
	glm::vec3 light_direction = m_spotlight_node.GetDirection();
	glm::vec3 light_color = m_spotlight_node.GetColor();
	glUniformMatrix4fv(m_geometry_rendering_program["uniform_light_projection_matrix"], 1, GL_FALSE, glm::value_ptr(m_spotlight_node.GetProjectionMatrix()));
	glUniformMatrix4fv(m_geometry_rendering_program["uniform_light_view_matrix"], 1, GL_FALSE, glm::value_ptr(m_spotlight_node.GetViewMatrix()));
	glUniform3f(m_geometry_rendering_program["uniform_light_position"], light_position.x, light_position.y, light_position.z);
	glUniform3f(m_geometry_rendering_program["uniform_light_direction"], light_direction.x, light_direction.y, light_direction.z);
	glUniform3f(m_geometry_rendering_program["uniform_light_color"], light_color.x, light_color.y, light_color.z);
	glUniform1f(m_geometry_rendering_program["uniform_light_umbra"], m_spotlight_node.GetUmbra());
	glUniform1f(m_geometry_rendering_program["uniform_light_penumbra"], m_spotlight_node.GetPenumbra());
	glUniform1i(m_geometry_rendering_program["uniform_cast_shadows"], (m_spotlight_node.GetCastShadowsStatus())? 1 : 0);
	// Set the sampler2D uniform to use texture unit 1
	glUniform1i(m_geometry_rendering_program["shadowmap_texture"], 1);
	// Bind the shadow map texture to texture unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, (m_spotlight_node.GetCastShadowsStatus()) ? m_spotlight_node.GetShadowMapDepthTexture() : 0);
	
	// Enable Texture Unit 0
	glUniform1i(m_geometry_rendering_program["uniform_diffuse_texture"], 0);
	glActiveTexture(GL_TEXTURE0);

	// TODO

	// draw the first object
	DrawGeometryNode(m_geometric_object1, m_geometric_object1_transformation_matrix, m_geometric_object1_transformation_normal_matrix);

	// draw the second object
	for (int i = 0; i < 29; i++) {
		DrawGeometryNode(m_geometric_object2[i], m_geometric_object2_transformation_matrix[i], m_geometric_object2_transformation_normal_matrix[i]);
	}

	// draw the third object
	DrawGeometryNode(m_geometric_object3, m_geometric_object3_transformation_matrix, m_geometric_object3_transformation_normal_matrix);

	//// draw the sixth pbject

	//DrawGeometryNode(m_geometric_object6, m_geometric_object6_transformation_matrix, m_geometric_object6_transformation_normal_matrix);

	//// draw the 7th pbject

	//DrawGeometryNode(m_geometric_object7, m_geometric_object7_transformation_matrix, m_geometric_object7_transformation_normal_matrix);

	//// draw the 8th pbject

	//DrawGeometryNode(m_geometric_object8, m_geometric_object8_transformation_matrix, m_geometric_object8_transformation_normal_matrix);

	//// draw the 9th pbject

	//DrawGeometryNode(m_geometric_object9, m_geometric_object9_transformation_matrix, m_geometric_object9_transformation_normal_matrix);

	for (Pirate* p : game->getPirates()) {
		// body
		DrawGeometryNode(p->getBody(), p->getBodyTM(), p->getBodyTNM());

		// sword
		DrawGeometryNode(p->getSword(), p->getSwordTM(), p->getSwordTNM());

		// leftfoot
		DrawGeometryNode(p->getLeftFoot(), p->getLeftFootTM(), p->getLeftFootTNM());

		//rightfoot
		DrawGeometryNode(p->getRightFoot(), p->getRightFootTM(), p->getRightFootTNM());

	}

	// draw the cannonballs
	for (CannonBall* cannonball : game->getCannonBalls()) {
		DrawGeometryNode(cannonball->getCannonBall(), cannonball->getCannonBallTM(), cannonball->getCannonBallTNM());
	}

	/*if (createdTowers.size() != 0) {
		for (int i = 0; i < createdTowers.size(); i++) {
			DrawGeometryNode(createdTowers[i], m_geometric_object10_transformation_matrix[i], m_geometric_object10_transformation_normal_matrix[i]);
		}
	}*/
	for (Tower* t : game->getCreatedTowers()) {
		DrawGeometryNode(t->getTower(), t->getTowerTM(), t->getTowerTNM());
	}



	// Draw all the transparent objects

	// Enable Blending
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (!game->getInRoad()) {
		// draw the fourth object
		DrawGeometryNode(m_geometric_object4, m_geometric_object4_transformation_matrix, m_geometric_object4_transformation_normal_matrix);
	}
	else {
		// draw the fifth object
		DrawGeometryNode(m_geometric_object5, m_geometric_object5_transformation_matrix, m_geometric_object5_transformation_normal_matrix);
	}

	glDepthMask(GL_TRUE);

	glBindVertexArray(0);
	m_geometry_rendering_program.Unbind();

	glDisable(GL_DEPTH_TEST);
	if(m_rendering_mode != RENDERING_MODE::TRIANGLES)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPointSize(1.0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawGeometryNode(GeometryNode* node, glm::mat4 model_matrix, glm::mat4 normal_matrix)
{
	glBindVertexArray(node->m_vao);
	glUniformMatrix4fv(m_geometry_rendering_program["uniform_model_matrix"], 1, GL_FALSE, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(m_geometry_rendering_program["uniform_normal_matrix"], 1, GL_FALSE, glm::value_ptr(normal_matrix));
	for (int j = 0; j < node->parts.size(); j++)
	{
		glm::vec3 diffuseColor = node->parts[j].diffuseColor;
		glm::vec3 specularColor = node->parts[j].specularColor;
		float shininess = node->parts[j].shininess;
		glUniform3f(m_geometry_rendering_program["uniform_diffuse"], diffuseColor.r, diffuseColor.g, diffuseColor.b);
		glUniform3f(m_geometry_rendering_program["uniform_specular"], specularColor.r, specularColor.g, specularColor.b);
		glUniform1f(m_geometry_rendering_program["uniform_shininess"], shininess);
		glUniform1f(m_geometry_rendering_program["uniform_has_texture"], (node->parts[j].textureID > 0) ? 1.0f : 0.0f);
		glBindTexture(GL_TEXTURE_2D, node->parts[j].textureID);

		glDrawArrays(GL_TRIANGLES, node->parts[j].start_offset, node->parts[j].count);
	}
}

void Renderer::DrawGeometryNodeToShadowMap(GeometryNode* node, glm::mat4 model_matrix, glm::mat4 normal_matrix)
{
	glBindVertexArray(node->m_vao);
	glUniformMatrix4fv(m_spot_light_shadow_map_program["uniform_model_matrix"], 1, GL_FALSE, glm::value_ptr(model_matrix));
	for (int j = 0; j < node->parts.size(); j++)
	{
		glDrawArrays(GL_TRIANGLES, node->parts[j].start_offset, node->parts[j].count);
	}
}

void Renderer::RenderToOutFB()
{
	// Bind the default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_screen_width, m_screen_height);
	
	// clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// disable depth testing and blending
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	// bind the post processing program
	m_postprocess_program.Bind();
	
	glBindVertexArray(m_vao_fbo);
	// Bind the intermediate color image to texture unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_fbo_texture);
	glUniform1i(m_postprocess_program["uniform_texture"], 0);
	// Bind the intermediate depth buffer to texture unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_fbo_depth_texture);	
	glUniform1i(m_postprocess_program["uniform_depth"], 1);

	glUniform1f(m_postprocess_program["uniform_time"], m_continous_time);
	glm::mat4 projection_inverse_matrix = glm::inverse(m_projection_matrix);
	glUniformMatrix4fv(m_postprocess_program["uniform_projection_inverse_matrix"], 1, GL_FALSE, glm::value_ptr(projection_inverse_matrix));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);

	// Unbind the post processing program
	m_postprocess_program.Unbind();
}

void Renderer::CameraMoveForward(bool enable)
{
	m_camera_movement.x = (enable)? 1 : 0;
}
void Renderer::CameraMoveBackWard(bool enable)
{
	m_camera_movement.x = (enable) ? -1 : 0;
}

void Renderer::CameraMoveLeft(bool enable)
{
	m_camera_movement.y = (enable) ? -1 : 0;
}
void Renderer::CameraMoveRight(bool enable)
{
	m_camera_movement.y = (enable) ? 1 : 0;
}

void Renderer::CameraLook(glm::vec2 lookDir)
{
	m_camera_look_angle_destination = glm::vec2(1, -1) * lookDir;
}

void Renderer::setGameState(GameState * game)
{
	this->game = game;
}

GameState * Renderer::getGameState()
{
	return game;
}

//void Renderer::TileSetPos(int x, int y)
//{
//	this->tileX = x;
//	this->tileY = y;
//}
//
//void Renderer::getRealPos(float& x, float& y) {
//	x = 9 - x * 2;
//	y = 9 - y * 2;
//}
//
//void Renderer::addTower(float x, float y) {
//	if (availableTowers.size() != 0) {
//		getRealPos(x, y);
//		// Check that no other towers are in this spot
//		for (Tower* t : createdTowers) {
//			if (t->getX() == x && t->getY() == y) {
//				// TODO
//				// If we found then [MESSAGE] OR [ANOTHER TILE COLOR] + return
//				return;
//			}
//		}
//		availableTowers.back()->setX(x);
//		availableTowers.back()->setY(y);
//		createdTowers.push_back(availableTowers.back());
//		availableTowers.pop_back();
//	}
//}
//
//void Renderer::removeTower(float x, float y) {
//
//	if (createdTowers.size() != 0) {
//		getRealPos(x, y);
//		unsigned short i = 0;
//		for (Tower* t : createdTowers) {
//			if (t->getX() == x && t->getY() == y) {
//				Tower* erased = createdTowers[i];
//				createdTowers.erase(createdTowers.begin() + i);
//				delete erased;
//				printf("Removed Tower at Pos %f,%f \n", x, y);
//			}
//			i++;
//		}
//	}
//}
//
//void Renderer::rearrangeTower(float x, float y) {
//
//	if (createdTowers.size() != 0) {
//		getRealPos(x, y);
//		unsigned short i = 0;
//		for (Tower* t : createdTowers) {
//			if (t->getX() == x && t->getY() == y) {
//				Tower* erased = createdTowers[i];
//				createdTowers.erase(createdTowers.begin() + i);
//				availableTowers.push_back(erased);
//				printf("Moved Tower from Pos %f,%f to available Towers \n", x, y);
//			}
//			i++;
//		}
//	}
//}
