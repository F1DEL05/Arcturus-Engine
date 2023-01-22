#include<iostream>
#include"Shader.hpp"
#include"SoundEngine.hpp"
#include"Character.hpp"
#include"WindowClass.hpp"
float length = 0.2f;
float vertices[] = {
	 length / 2, length / 2,0.0f,
	 length / 2,-length / 2,0.0f,
	-length / 2,-length / 2,0.0f,
	 length / 2, length / 2,0.0f,
	-length / 2,length / 2,0.0f,
	-length / 2,-length / 2,0.0f
};
int main() {
	Window window(800, 600, "Arcturus Engine", GL_FALSE, 3, 3);
	window.StartGL();

	Shader* program = new Shader();
	program->AddShader("./Shaders/vshader.glsl", Shader::VERTEX_SHADER);
	program->AddShader("./Shaders/fshader.glsl", Shader::FRAGMENT_SHADER);
	program->Link();
	program->DeleteShaders();
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
	program->ConnectUniformVariable("uMove");
	program->ConnectUniformVariable("uColor");
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
	float speed = 0.02f;
	SoundEngine sound;
	sound.playSound("a.mp3");
	Character chr1(0.02f, 0.0, 0.0, Character::DIRECTION_RIGHT);
	while (!window.Check_windowClose()) {
		if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
		{
			glfwTerminate();
			glfwDestroyWindow(window.getWindow());
			sound.stopSound();
			break;
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_RIGHT))
		{
			chr1.setDirection(Character::DIRECTION_RIGHT);
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT))
		{
			chr1.setDirection(Character::DIRECTION_LEFT);

		}if (glfwGetKey(window.getWindow(), GLFW_KEY_UP))
		{
			chr1.setDirection(Character::DIRECTION_UP);

		}if (glfwGetKey(window.getWindow(), GLFW_KEY_DOWN))
		{



		}
		chr1.move();
		program->SetVec3("uMove", chr1.getPosition());
		program->SetVec4("uColor", glm::vec4(0.5f, 0.0f, 0.5f, 1.0));





		window.bgcolor(0.0f, 0.0f, 0.0f);
		program->UseProgram();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, (sizeof(vertices) / sizeof(vertices[0])) / 3);
		program->DeleteProgram();
		window.loop_events();
	}
}