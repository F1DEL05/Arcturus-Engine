#ifndef WINDOWCLASS_HPP
#define WINDOWCLASS_HPP

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
class Window {
public:

	Window(int width, int heigth, const char* title, bool Resizeable, int version_major, int version_minor);
	bool Check_windowClose();
	void StartGL();
	GLFWwindow* getWindow();
	void loop_events();
	void bgcolor(float r, float g, float b);
private:
	GLFWwindow* window;
};
#endif 