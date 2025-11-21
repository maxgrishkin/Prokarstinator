#include <complex>
#include <cstring>
#include "GLinclude.h"
#include <fstream>
#include <iostream>
#include "../Render/ShaderProgram.h"
#include "../Resource/ResourceManager.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

GLfloat point[] = {
	0.0f,50.f,0.0f,
	50.f,-50.f,0.0f,
	-50.f,-50.0f,0.0f
};

GLfloat colors[] = {
	1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f
};

GLfloat texCoord[] {
	0.5f,1.0f,
	1.0f,0.0f,
	0.0f,0.0f
};

glm::ivec2 gl_WINDOWS_SIZE(640,480);

void glfwWindowScaleCallback(GLFWwindow* pWindow,int width,int height) {
	gl_WINDOWS_SIZE.x = width;
	gl_WINDOWS_SIZE.y = height;
	glViewport(0,0,width,height);
}

void glfwKeyCallback(GLFWwindow* pWindow,int key,int scancode,int action,int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(pWindow,1);
	}
}

int main(int argc,char** argv)
{
	GLFWwindow* pwindow;

	/* Initialize the library */
	if (!glfwInit())
		throw std::runtime_error("glfwInit-failed!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	pwindow = glfwCreateWindow(gl_WINDOWS_SIZE.x, gl_WINDOWS_SIZE.y, "Prokarstinator", nullptr, nullptr);
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

	glClearColor(0,0,0,1);
	{
		ResourceManager resourceManager(argv[0]);
		auto pDefaultShaderProgram = resourceManager.loadShader("DefaultShader", "res/shaders/shader.vsh", "res/shaders/shader.fsh");

		std::string vertex_shader_code;
		std::string fragment_shader_code;

		if (!pDefaultShaderProgram->isCompiled()) {
			throw std::runtime_error("Can't create shader program!");
		}

		auto tex = resourceManager.loadTexture("DefaultTexture","res/textures/minion.png");

		GLuint points_vbo = 0;
		glGenBuffers(1,&points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER,points_vbo);

		glBufferData(GL_ARRAY_BUFFER,sizeof(point),point,GL_STATIC_DRAW);

		GLuint colors_vbo = 0;
		glGenBuffers(1,&colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER,colors_vbo);

		glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);

		GLuint texCoord_vbo = 0;
		glGenBuffers(1,&texCoord_vbo);
		glBindBuffer(GL_ARRAY_BUFFER,texCoord_vbo);

		glBufferData(GL_ARRAY_BUFFER,sizeof(texCoord),texCoord,GL_STATIC_DRAW);

		GLuint vao = 0;
		glGenVertexArrays(1,&vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,points_vbo);
		glVertexAttribPointer(0,3,GL_FLOAT,0,0,nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER,colors_vbo);
		glVertexAttribPointer(1,3,GL_FLOAT,0,0,nullptr);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER,texCoord_vbo);
		glVertexAttribPointer(2,2,GL_FLOAT,0,0,nullptr);

		pDefaultShaderProgram->use();
		pDefaultShaderProgram->setInt("tex",0);

		glm::mat4 modeMatrix_1 = glm::mat4(1.f);
		modeMatrix_1 = glm::translate(modeMatrix_1,glm::vec3(100.f,50.f,0.f));

		glm::mat4 modeMatrix_2 = glm::mat4(1.f);
		modeMatrix_2 = glm::translate(modeMatrix_2,glm::vec3(590.f,50.f,0.f));

		glm::mat4 projectionMatrix = glm::ortho(0.f,static_cast<float>(gl_WINDOWS_SIZE.x),0.f,static_cast<float>(gl_WINDOWS_SIZE.y),-100.f,100.f);

		pDefaultShaderProgram->setMatrix4("projectionMat",projectionMatrix);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(pwindow))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			pDefaultShaderProgram->use();
			glBindVertexArray(vao);
			tex->bind();

			pDefaultShaderProgram->setMatrix4("modelMat",modeMatrix_1);
			glDrawArrays(GL_TRIANGLES,0,3);

			pDefaultShaderProgram->setMatrix4("modelMat",modeMatrix_2);
			glDrawArrays(GL_TRIANGLES,0,3);

			/* Swap front and back buffers */
			glfwSwapBuffers(pwindow);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}