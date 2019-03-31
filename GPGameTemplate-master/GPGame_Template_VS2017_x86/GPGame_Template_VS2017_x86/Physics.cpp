#pragma once
#include "Physics.h"

glm::vec3 accelleration  = glm::vec3(0.5, 0.0f, 0.5f);

Physics::Physics() {
	touchGround = false;					// Has touched ground
	mass = 3.0f;							// Default mass of 2 units
	size = glm::vec3(1.0f, 1.0f, 1.0f);

}


Physics::Physics(glm::vec3 _size) {
	Physics::Physics();
	size = _size;
}




// Update value in cur_vel to new value
void updateVelocity(Physics &obj, float deltaTime) {
	obj.velocity =  obj.velocity + (accelleration * deltaTime);
}


// Update value in cur_pos to new value	
void updatePosition(Physics &obj, float deltaTime) {
	obj.position = obj.position + (obj.velocity * deltaTime);

}
