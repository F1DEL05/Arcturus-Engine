#include"WindowClass.hpp" 
Window::Window(int width,int heigth, const char* title,bool Resizeable,int version_major,int version_minor) {
	if (!glfwInit()) {
		std::cout << std::endl << "glfw Baslatilamadi !";
		glfwTerminate();
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE,Resizeable);
	window = glfwCreateWindow(width, heigth, title, NULL, NULL);
	if (window==nullptr)
	{
		std::cout << std::endl << "Pencere Baslatilamadi !";
		glfwTerminate();
	}
}
 void Window::StartGL() {
	glfwMakeContextCurrent(window);
	if (glewInit()!=GLEW_OK)
	{
		std::cout << std::endl << "glew Baslatilamadi !";
		glfwTerminate();
		glfwDestroyWindow(window);
	};
	glewExperimental == GL_TRUE;
}
bool Window::Check_windowClose() {
	return glfwWindowShouldClose(window);
}
GLFWwindow* Window::getWindow() {
	return window;
}
 void Window::loop_events() {
	glfwPollEvents();
	glfwSwapBuffers(window);
}
 void Window::bgcolor(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}