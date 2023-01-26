#include<iostream>
#include"Shader.hpp"
#include"SoundEngine.hpp"
#include"Character.hpp"
#include"WindowClass.hpp"
#include<vector>

#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
float length = 1.0f;
float vertices[] = {
	 length / 2, length / 2,0.0f, 1.0f,0.0f,0.0f, 1.0f,1.0f,
	 length / 2,-length / 2,0.0f, 1.0f,0.0f,1.0f, 1.0f,0.0f,
	-length / 2,-length / 2,0.0f, 1.0f,1.0f,0.0f, 0.0f,0.0f,
	-length / 2, length / 2,0.0f, 0.0f,1.0f,1.0f, 0.0f,1.0f
};
unsigned int indices[] = {
	0,1,3,
	1,2,3
};
void move(Character& chr1, Character::DIRECTION DIR) {
	chr1.SetDirection(DIR);
	chr1.move();
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * (sizeof(float)), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//*------------------------------------------
	int width, height, nrChannels;
	unsigned int texture;

	unsigned char* data = stbi_load("./images/mevlana1923.png", &width, &height, &nrChannels, 0);
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	//------------------------
	glGenerateMipmap(GL_TEXTURE_2D);
	//----------------------
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

	program.ConnectUniformVariable("texture_uniform");
	program.ConnectUniformVariable("uMtx");
	program.ConnectUniformVariable("uMove");

	glm::mat3 aaa;
	SoundEngine* sound = new SoundEngine();
	sound->playSound("./sound/a.mp3");
	system("cls");
	float angle = 0.0f, speedr = 5.0f, speedm = 0.02f, scale = 0.4f;
	Character chr1(speedm, 0, 0);

	while (!window.Check_windowClose() && glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS) {
		aaa = chr1.GetRotationMatrix() * chr1.GetScale();
		if (glfwGetKey(window.getWindow(), GLFW_KEY_RIGHT))
		{
			move(chr1, Character::DIR_R);
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT))
		{
			move(chr1, Character::DIR_L);
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_UP))
		{
			move(chr1, Character::DIR_U);
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_DOWN))
		{
			move(chr1, Character::DIR_D);
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_K))
		{
			scale += 0.05f;
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_L))
		{
			if (scale<=0)
			{
				scale = 0;
			}
			else {
				scale -= 0.05f;
			}
			}if (glfwGetKey(window.getWindow(), GLFW_KEY_O))
		{
			if (speedr >= 45)
			{

			}
			else
			{
				speedr++;
			}
		}if (glfwGetKey(window.getWindow(), GLFW_KEY_P))
		{
			if (speedr <= 0)
			{

			}
			else {
				speedr--;
			}
		}




		angle += speedr;
		chr1.SetRotation(angle);
		program.SetVec3("uMove", chr1.getPosition());
		chr1.SetScale(glm::vec2(scale, scale));
		program.SetMat3("uMtx", &aaa);
		window.bgcolor(0, 0, 0);
		program.UseProgram();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, indices);
		glBindVertexArray(0);
		program.DeleteProgram();
		window.loop_events();
	}
	sound->stopSound();
}