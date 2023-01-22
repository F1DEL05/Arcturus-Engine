#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include<glm/vec3.hpp>
#include<GL/glew.h>
class Character {
public:
	enum DIRECTION
	{
		DIRECTION_RIGHT=1,
		DIRECTION_LEFT=-1,
		DIRECTION_UP=2
	};
	void move();
	void setDirection(Character::DIRECTION dir);
	Character::DIRECTION getDirection();
	Character(float speed,float x,float y,Character::DIRECTION dir);
	glm::vec3 getPosition();
private:
	glm::vec3 start_pos;
	float speed;
	Character::DIRECTION direction;
};
#endif // !1
