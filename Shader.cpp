#include "Shader.hpp"
Shader::Shader() {
	programID = glCreateProgram();
}
void Shader::AddShader(std::string FileName,Shader::SHADER_TYPE shader_type) {
	GLenum shader;
	if (shader_type==0)
	{
		shader = GL_VERTEX_SHADER;
	}
	else {
		shader = GL_FRAGMENT_SHADER;
	}
	shaderID[shader_type] = glCreateShader(shader);
	std::string data;
	std::ifstream file(FileName);
	if (file.is_open())
	{
		char a;
		while ((a = file.get()) != EOF) {
			data += a;
		}
	}
	file.close();
	const char* data_ptr = &data[0];
	glShaderSource(shaderID[shader_type], 1, &data_ptr, 0);
	glCompileShader(shaderID[shader_type]);
	Shader_Compile_Exception(shader_type);
	glAttachShader(programID, shaderID[shader_type]);
	
}
void Shader::Shader_Compile_Exception(Shader::SHADER_TYPE shaderType) {
	int success = 1;
	char errorLog[512];
	glGetShaderiv(shaderID[shaderType], GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID[shaderType], sizeof(errorLog), NULL, errorLog);
		std::cout << std::endl << "Shader Compile Error : " << errorLog;
	}
}
void Shader::Program_Link_Exception() {
	int success = 1;
	char errorLog[512];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, sizeof(errorLog), NULL, errorLog);
		std::cout << std::endl << "Program Link Error : " << errorLog;
	}
}
void Shader::Link() {
	glLinkProgram(programID);
	Program_Link_Exception();
}
void Shader::DeleteProgram() {
	glDeleteProgram(programID);
}
void Shader::DeleteShaders() {
	glDeleteShader(shaderID[0]);
	glDeleteShader(shaderID[1]);
}
void Shader::UseProgram() {
	glUseProgram(programID);
}
void Shader::ConnectUniformVariable(std::string uniform_var_name) {
	var_List[uniform_var_name] = glGetUniformLocation(programID, uniform_var_name.c_str());
}
void Shader::SetVec3(std::string uniform_var_name,glm::vec3 vector3) {
	glUniform3f(var_List[uniform_var_name], vector3.x, vector3.y, vector3.z);
}
void Shader::SetVec4(std::string uniform_var_name,glm::vec4 vector4) {
	glUniform4f(var_List[uniform_var_name], vector4.r, vector4.g, vector4.b,vector4.a);
}
void Shader::SetMat3(std::string uniform_var_name, glm::mat3 *matrix3x1) {
	glUniformMatrix3fv(var_List[uniform_var_name], 1, false,(GLfloat*)matrix3x1);
}
unsigned int Shader::getProgram() {
	return programID;
}