#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include<glm/vec3.hpp>
#include<glm/gtx/matrix_transform_2d.hpp>
#include<glm/mat3x3.hpp>
#include<GL/glew.h>
class Character {
public:
	enum DIRECTION
	{
		DIR_R=1,
		DIR_L=-1,
		DIR_U=2,
		DIR_D=-2
	};
	Character(float speed, float x, float y);
	glm::vec3 getPosition();
	void SetRotation(float angle);
	glm::mat3 GetRotationMatrix();
	void SetScale(glm::vec2 vector);
	glm::mat3 GetScale();
	void move();
	void SetDirection(Character::DIRECTION dir);
	Character::DIRECTION GetDirection();
private:
	glm::vec3 start_pos;
	float speed;
	Character::DIRECTION dir;
	glm::mat3 matrix3_rotation,matrix3_scale,matrix3_translate;
};
#endif // !1
