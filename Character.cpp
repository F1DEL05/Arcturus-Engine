#include"Character.hpp"
Character::Character(float speed, float x, float y) {
	start_pos = glm::vec3(x,y,1.0f);
	this->speed = speed;
	this->dir = dir;
}
glm::vec3 Character::getPosition() {
	return start_pos;
}
void Character::SetRotation(float angle) {
	matrix3_rotation = glm::rotate(glm::mat3(1), glm::radians(angle));
}
glm::mat3 Character::GetRotationMatrix() {
	return matrix3_rotation;
}
void Character::SetScale(glm::vec2 vector) {
	matrix3_scale = glm::scale(glm::mat3(1), vector);
}
glm::mat3 Character::GetScale() {
	return matrix3_scale;
}
void Character::SetDirection(Character::DIRECTION dir) {
	this->dir = dir;
}
Character::DIRECTION Character::GetDirection() {
	return dir;
}
void Character::move() {
	switch (dir)
	{
	case Character::DIR_R:
		start_pos += glm::vec3(speed,0,0);
		break;
	case Character::DIR_L:
		start_pos += glm::vec3(-speed, 0, 0);
		break;
	case Character::DIR_U:
		start_pos += glm::vec3(0,speed, 0);
		break;
	case Character::DIR_D:
		start_pos += glm::vec3(0, -speed, 0);
		break;
	}
}
