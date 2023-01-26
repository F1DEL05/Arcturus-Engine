#ifndef VertexBufferObject_hpp
#define VertexBufferObject_hpp
#include<iostream>
#define STB_IMAGE_IMPLEMENTATION

#include<GL/glew.h>
#include<GLFW/glfw3.h>
class VertexBuffer {

public:
	VertexBuffer();
	void AddTexture();
	void IndexBuffer();
	



private:
	unsigned int vao, vbo, ibo;

};






#endif // !VertexBufferObject_hpp
