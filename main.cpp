#include <complex>
#include <iostream>
#include "external/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

int gl_WINDOWS_SIZE_X = 640;
int gl_WINDOWS_SIZE_Y = 480;

void glfwWindowScaleCallback(GLFWwindow* pWindow,int width,int height) {
	gl_WINDOWS_SIZE_X = width;
	gl_WINDOWS_SIZE_Y = height;
	glViewport(0,0,width,height);
}

void glfwKeyCallback(GLFWwindow* pWindow,int key,int scancode,int action,int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(pWindow,1);
	}
}

int main()
{
	GLFWwindow* pwindow;

	/* Initialize the library */
	if (!glfwInit())
		throw std::runtime_error("glfwInit-failed!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	pwindow = glfwCreateWindow(gl_WINDOWS_SIZE_X, gl_WINDOWS_SIZE_Y, "Prokarstinator", nullptr, nullptr);
	if (!pwindow)
	{
		glfwTerminate();
		throw std::runtime_error("glfwCreateWindow-failed!");
	}

	glfwSetWindowSizeCallback(pwindow,glfwWindowScaleCallback);
	glfwSetKeyCallback(pwindow,glfwKeyCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(pwindow);

	if (!gladLoadGL()) {
		throw std::runtime_error("can't load GLAD");
	}

	std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL-version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(1,0,0,1);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(pwindow))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(pwindow);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}