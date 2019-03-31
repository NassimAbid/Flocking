#include "Particles.h"




ParticleEmitter::ParticleEmitter(Cube *_cube) 
	: generator(std::random_device()()) // seed the generator
	{


		x_from = -3.0f;
		x_to = 3.0f;

		y_from = 1.0f;
		y_to = 1.0f;

		z_from = -2.0f;
		z_to = 2.0f;

		target_x_from = -2.0f;
		target_x_to = 2.0f;


		target_z_from = -2.0f;
		target_z_to = 2.0f;


	

	Cubes = _cube;
}

float ParticleEmitter::getRand(float from, float to) {
	std::uniform_real_distribution<float> dis(from, to);
	return dis(generator);
}

float ParticleEmitter::makeleader() {
	float leader_chance = getRand(leader_from, leader_to);

	if (leader_chance > 0.95) {
		return true;
	}else
		return false;
	
}

float ParticleEmitter::x_getRand() {
	return getRand(x_from, x_to);
}

float ParticleEmitter::y_getRand() {
	return getRand(y_from, y_to);
}

float ParticleEmitter::z_getRand() {
	return getRand(z_from, z_to);
}

glm::vec3 ParticleEmitter::getdifference(Boid &obj) {
	
	return obj.target - obj.physicsAttr->position;
}

glm::vec3 ParticleEmitter::GetTargetLoc(){
	float x_target = getRand(target_x_from, target_x_to);
	float z_target = getRand(target_x_from, target_x_to);

	targetloc = glm::vec3(x_target, 1.0f, z_target);
	return targetloc;
}

void swarmVelocity(Boid &obj, glm::vec3 diff, float deltatime) {

	if (obj.physicsAttr->velocity.x > obj.max_speed) {
		obj.physicsAttr->velocity.x = obj.max_speed;
	}
	else if (diff.x <= 0.0f) {
		obj.physicsAttr->velocity.x -= 1.0 *deltatime;
	}
	else {
		obj.physicsAttr->velocity.x += 1.0 *deltatime;
	}

	if (obj.physicsAttr->velocity.z > obj.max_speed) {
		obj.physicsAttr->velocity.z = obj.max_speed;
	}
	else if (diff.z <= 0.0f) {
		obj.physicsAttr->velocity.z -= 1.0 *deltatime;
	}
	else {
		obj.physicsAttr->velocity.z += 1.0 *deltatime;
	}


}





void ParticleEmitter::start(glm::vec3 position) {

	pos = position;

	cout << "started\n";

	// Grab current time
	auto time_start = Time::now();
	auto time_compare = Time::now();

	//the current leader of each particle 
	int cur_leader;

	//gets new target location

	



	for (int i = 0; i < MaxParticles; i++) {
		// Generate random x, y, z pos
		float x_pos = x_getRand();
		float z_pos = z_getRand();


		boid[i].leader = makeleader();

		if (i == 0) {

			boid[i].leader = true;
			boid[i].target = GetTargetLoc();
			cur_leader = i;
			Cubes[i].fillColor = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);

		}else if(boid[i].leader == true){
			Cubes[i].fillColor =glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
			cur_leader = i;
			boid[i].target = boid[0].physicsAttr->position;
		//	cout << i << "is leader\n";
		} else {
			boid[i].lead_by = cur_leader;
			boid[i].target = boid[cur_leader].physicsAttr->position;
	
		}
			
		boid[i].physicsAttr = new Physics;

		// Set velocity values
		boid[i].physicsAttr->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		boid[i].physicsAttr->size = glm::vec3(0.1f, 0.1f, 0.1f);

		// Init starting position of particle
		boid[i].physicsAttr->position = glm::vec3(x_pos, 1.0f, z_pos);


	}
}


void ParticleEmitter::update(float deltatime) {

	
	
	for (int i = 0; i < MaxParticles; i++) {

		
	
	

		//gets refereshed target location every 3 seconds
		if (i == 0 && compareTime(boid[i].updated) >= 10.0) {
			boid[i].updated = Time::now();
			boid[i].target = GetTargetLoc();
			cout << boid[i].target.x << "\n";
		}
		else if(i==0){
			boid[i].target = boid[i].target;
			}
			else {
				boid[i].target = boid[boid->lead_by].physicsAttr->position;
				//cout << "leader: " << i << " x:" << boid[i].target.x << "z:" << boid[i].target.z << "\n";
			}
		


		glm::vec3 diff = getdifference(boid[i]);
		//cout << i<<"diff x: " << diff.x<<" Z: "<<diff.z<<"\n";
		//updatePosition(*boid[i].physicsAttr, deltatime);

		swarmVelocity(boid[i], diff, deltatime);
		//cout << "diff x: " << diff.x<<" Z: "<<diff.z;

	//	updateVelocity(*boid[i].physicsAttr, deltatime);
		updatePosition(*boid[i].physicsAttr, deltatime);


		glm::mat4 mv_matrix_cube =
			glm::translate(boid[i].physicsAttr->position) *
			glm::mat4(1.0f);
		mv_matrix_cube *= glm::scale(boid[i].physicsAttr->size);

		// Update cubes matrix
		Cubes[i].mv_matrix = myGraphics.viewMatrix * mv_matrix_cube;
		Cubes[i].proj_matrix = myGraphics.proj_matrix;

	}
	
}

float ParticleEmitter::compareTime(std::chrono::steady_clock::time_point t0) {
	// calc time since start
	auto t1 = Time::now();	// grab current time
	fsec fs = t1 - t0;		// find difference

	// output difference in seconds
	return fs.count();
}

