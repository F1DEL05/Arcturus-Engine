#include"Character.hpp"
Character::Character(float speed, float x, float y,Character::DIRECTION dir) {
	start_pos = glm::vec3(x,y,0.0f);
	this->speed = speed;
	direction = dir;
}
void Character::setDirection(Character::DIRECTION dir) {
	direction = dir;
}
Character::DIRECTION Character::getDirection() {
	return direction;
}
void Character::move() {
	switch (direction)
	{
	case Character::DIRECTION_RIGHT:
		start_pos += glm::vec3(speed,0.0f,0.0f);
		break;
	case Character::DIRECTION_LEFT:
		start_pos += glm::vec3(-speed,0.0f,0.0f);
		break;
	case Character::DIRECTION_UP:
		//------------------------
		//-----------------------
		//Gravity will be added
		//-----------------------
		//------------------------
		break;
	}
}
glm::vec3 Character::getPosition() {
	return start_pos;
}