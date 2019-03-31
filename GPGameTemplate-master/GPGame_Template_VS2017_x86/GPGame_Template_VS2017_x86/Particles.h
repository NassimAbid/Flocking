#pragma once
#include "Global.h"
#include <iostream>
#include <vector>
#include <random>
#include <time.h>       /* time */
// Helper graphic libraries
#include <GL/glew.h>
#include <chrono> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "Shapes.h"
#include "Physics.h"


class Physics;

struct Boid {
	Physics* physicsAttr;
	bool leader;
	int lead_by;


	float max_speed =2.0f;
	float max_force;

	glm::vec3 target;

	std::chrono::steady_clock::time_point updated;

};


class ParticleEmitter {
private:
	Boid boid[MaxParticles];
	
	glm::vec3 pos;

	// Acceleration for the
	glm::vec3 accelleration;

	// Use chrono for decimal time points
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;

	// Generator from random float
	std::mt19937							generator;

	float x_from;
	float x_to;

	float y_from;
	float y_to;

	float z_from;
	float z_to;


	float target_x_from;
	float target_x_to;


	float target_z_from;
	float target_z_to;

	float leader_from = 0.0f;
	float leader_to = 1.0f;

	glm::vec3 targetloc;

	float getRand(float from, float to);

	float x_getRand();

	float y_getRand();

	float z_getRand();

	float makeleader();

	glm::vec3 getdifference(Boid &obj);

	glm::vec3 GetTargetLoc();


public:
	// Class Constructor
	ParticleEmitter();

	ParticleEmitter(Cube *_cube);

	Cube *Cubes;

	// Set pointer to floor for collisions
	Physics* floor;

	void start(glm::vec3 position);


	void update(float deltatime);

	float compareTime(std::chrono::steady_clock::time_point t0);

};