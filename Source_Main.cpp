#include<iostream>
#include"Shader.hpp"
#include"SoundEngine.hpp"
#include"Character.hpp"
#include"WindowClass.hpp"
#include<vector>
#include<cstdlib>
float length = 0.1f;
float vertices[] = {
	-length / 2,length / 2,
	-length / 2,-length / 2,
	length / 2,length / 2,
	length / 2,-length / 2
};
unsigned int indices[] = {
	0,1,2,
	2,3,1
};
std::vector<Character*> vec1, vec2;
void drawA(Shader& program, std::vector<Character*>& vec1, glm::vec4 color) {
	for (auto vec : vec1)
	{
		glm::mat3 a = vec->GetRotationMatrix() * vec->GetScale();
		program.SetVec3("uMove", vec->getPosition());
		program.SetVec4("uColor", color);
		program.SetMat3("uMtx", &a);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, indices);
	}
}

void rotate(std::vector<Character*>& vector, float& angle) {
	for (auto next : vector)
	{
		next->SetRotation(angle);
	}
}
void scale(std::vector<Character*> vector1, glm::vec2 vector) {
	for (auto next : vector1)
	{
		next->SetScale(vector);
	}
}
void move(std::vector<Character*> vector1, Character::DIRECTION dir) {
	for (auto next : vector1)
	{
		next->SetDirection(dir);
		next->move();
	}
}
int main() {
	Window window(800, 600, "Arcturus Engine", GL_FALSE, 3, 3);
	window.StartGL();

	Shader program;
	program.AddShader("./Shaders/vshader.glsl", Shader::VERTEX_SHADER);
	program.AddShader("./Shaders/fshader.glsl", Shader::FRAGMENT_SHADER);
	program.Link();
	program.DeleteShaders();
	//*----------------------------------------
	unsigned int vao, vbo, ibo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ibo), &ibo, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * (sizeof(GL_FLOAT)), 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//*------------------------------------------


	float angle = 15.0f;


	program.ConnectUniformVariable("uMove");
	program.ConnectUniformVariable("uColor");
	program.ConnectUniformVariable("uMtx");
	float speedrotate = 1.0f;

	float speed = 0.02f;

	SoundEngine sound;
	sound.playSound("a.mp3");

	float seed = 0.0f;
	float scalex = 1.0f;
	vec1.push_back(new Character(speed, 0.0f, 0.0f));
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
			move(vec1, Character::DIR_R);
		}
		if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT))
		{
			move(vec1, Character::DIR_L);
		}
		if (glfwGetKey(window.getWindow(), GLFW_KEY_UP))
		{
			move(vec1, Character::DIR_U);
		}
		if (glfwGetKey(window.getWindow(), GLFW_KEY_DOWN))
		{
			move(vec1, Character::DIR_D);
		}

		if (glfwGetKey(window.getWindow(), GLFW_KEY_O))
		{
			if (abs(speedrotate) == 45)
			{
				
			}
			else {
				speedrotate++;
			}std::cout << std::endl << speedrotate << "derece";
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_P))
		{
			if (abs(speedrotate)==1)
			{

			}
			else {
				speedrotate--;
			}
			std::cout << std::endl << speedrotate << "derece";
			
		}
		if (glfwGetKey(window.getWindow(), GLFW_KEY_K))
		{
			
				scalex += 0.1f;
			
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_L))
		{
			if (scalex <= 0.0f) {
				
			}
			else {
				scalex -= 0.1f;
			}
		}
		//amnskm max hýz 45 dereceymis

		angle += speedrotate;
		rotate(vec1, angle);
		scale(vec1, glm::vec2(scalex, scalex));





		window.bgcolor(0.0f, 0.0f, 0.0f);
		program.UseProgram();
		glBindVertexArray(vao);
		drawA(program, vec1, glm::vec4(0.0f, 0.7f, 0.7f, 1.0f));
		program.DeleteProgram();
		window.loop_events();
	}
	vec1.clear();
	vec2.clear();
}