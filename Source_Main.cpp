#include<iostream>
#include"Shader.hpp"
#include"SoundEngine.hpp"
#include"Character.hpp"
#include"WindowClass.hpp"
#include<vector>
#include<cstdlib>
float length = 0.1f;
float vertices[] = {
	 length / 2, length / 2,0.0f,
	 length / 2,-length / 2,0.0f,
	-length / 2,-length / 2,0.0f,
	 length / 2, length / 2,0.0f,
	-length / 2,length / 2,0.0f,
	-length / 2,-length / 2,0.0f
};
std::vector<Character*> vec1, vec2;
void drawA(Shader& program, std::vector<Character*>& vec1, glm::vec4 color) {
	for (auto vec : vec1)
	{
		glm::mat3 a = vec->GetRotationMatrix();
		program.SetVec3("uMove", vec->getPosition());
		program.SetVec4("uColor", color);
		program.SetMat3("uMtx", &a);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
void moveA(Character::DIRECTION dir) {
	for (auto next : vec1)
	{
		next->setDirection(dir);
		next->move();
	}
}
void moveB(Character::DIRECTION dir) {
	for (auto next : vec2)
	{
		next->setDirection(dir);
		next->move();
	}
}
void rotate(std::vector<Character*>& vector, float& angle) {
	for (auto next : vector)
	{
		next->SetRotation(angle);
	}
}
int main() {
	Window window(700, 700, "Arcturus Engine", GL_FALSE, 3, 3);
	window.StartGL();

	Shader program;
	program.AddShader("./Shaders/vshader.glsl", Shader::VERTEX_SHADER);
	program.AddShader("./Shaders/fshader.glsl", Shader::FRAGMENT_SHADER);
	program.Link();
	program.DeleteShaders();
	//*----------------------------------------
	unsigned int vao, vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(GL_FLOAT)), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//*------------------------------------------

	glm::mat3 transform(1);
	float angle = 15.0f;
	glm::mat3 matrix;


	program.ConnectUniformVariable("uMove");
	program.ConnectUniformVariable("uColor");
	program.ConnectUniformVariable("uMtx");
	float speedrotate = 1.0f;

	float speed = 0.02f;

	SoundEngine sound;
	sound.playSound("a.mp3");

	float seed = 0.0f;
	vec1.push_back(new Character(speed, -0.5f, 0.0f, Character::DIRECTION_RIGHT));
	vec1.push_back(new Character(speed, -0.5f, 0.5f, Character::DIRECTION_RIGHT));
	vec1.push_back(new Character(speed, 0.0f, 0.5f, Character::DIRECTION_RIGHT));
	vec1.push_back(new Character(speed, 0.0f, 0.0f, Character::DIRECTION_RIGHT));
	vec2.push_back(new Character(speed, 0.5f, 0.0f, Character::DIRECTION_RIGHT));
	vec2.push_back(new Character(speed, 0.5f, -0.5f, Character::DIRECTION_RIGHT));
	vec2.push_back(new Character(speed, 0.0f, -0.5f, Character::DIRECTION_RIGHT));
	vec2.push_back(new Character(speed, 0.0f, 0.0f, Character::DIRECTION_RIGHT));
	while (!window.Check_windowClose()) {
		if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
		{
			glfwTerminate();
			glfwDestroyWindow(window.getWindow());
			sound.stopSound();
			break;
		}
		if (glfwGetKey(window.getWindow(), GLFW_KEY_RIGHT))
		{
			moveA(Character::DIRECTION_RIGHT);
		}
		if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT))
		{
			moveA(Character::DIRECTION_LEFT);
		}
		if (glfwGetKey(window.getWindow(), GLFW_KEY_UP))
		{
			moveA(Character::DIRECTION_UP);
		}
		if (glfwGetKey(window.getWindow(), GLFW_KEY_DOWN))
		{
			moveA(Character::DIRECTION_DOWN);
		}
		if (glfwGetKey(window.getWindow(), GLFW_KEY_W))
		{
			moveB(Character::DIRECTION_UP);
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_A))
		{
			moveB(Character::DIRECTION_LEFT);
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_S))
		{
			moveB(Character::DIRECTION_DOWN);
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_D))
		{
			moveB(Character::DIRECTION_RIGHT);
		}
		if (glfwGetKey(window.getWindow(), GLFW_KEY_O))
		{
			if (abs(speedrotate) == 45)
			{

			}
			else {
				speedrotate--;
			}
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_P))
		{
			if (abs(speedrotate) == 1)
			{

			}
			else {
				speedrotate++;
			}
		}
		//amnskm max hýz 45 dereceymis
		angle -= speedrotate;
		rotate(vec1, angle);
		rotate(vec2, angle);


		window.bgcolor(0.0f, 0.0f, 0.0f);
		program.UseProgram();
		glBindVertexArray(vao);
		drawA(program, vec1, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		drawA(program, vec2, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		program.DeleteProgram();
		window.loop_events();
	}
	vec1.clear();
	vec2.clear();
}