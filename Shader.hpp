#ifndef SHADER_HPP
#define SHADER_HPP
#include<iostream>
#include<GL/glew.h>
#include<fstream>
#include <map>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/gtx/matrix_transform_2d.hpp>
#include<glm/mat3x3.hpp>
class Shader {
public:
	enum SHADER_TYPE
	{
		VERTEX_SHADER = 0,
		FRAGMENT_SHADER = 1
	};
	Shader();
	void AddShader(std::string FileName, Shader::SHADER_TYPE shader_type);
	void Link();
	void DeleteProgram();
	void DeleteShaders();
	void UseProgram();
	unsigned int getProgram();
	void SetInt(std::string uniform_var_name,int a);
	//------------------------
	void ConnectUniformVariable(std::string uniform_var_name);
	void SetVec3(std::string uniform_var_name,glm::vec3 vector3);
	void SetVec4(std::string uniform_var_name,glm::vec4 vector4);
	void SetMat3(std::string uniform_var_name, glm::mat3 *matrix3x1);
private:
	void Program_Link_Exception();
	void Shader_Compile_Exception(Shader::SHADER_TYPE shaderType);

	unsigned int programID;
	unsigned int shaderID[2];
	std::map<std::string, int> var_List;
};
#endif // !SHADER_HPP
