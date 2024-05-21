//������ ������Ʈ��: Lecture04_HW
//idle : ȭ��� ���������� clear
//���콺 ������ KeyDown�ϸ� : ������
//���콺 ������ KeyUp�ϸ� : ���󺹱�
//���콺 ���� KeyDown�ϸ� : ���
//���콺 ���� KeyUp�ϸ� : ���󺹱�
//���콺 ������ KeyDown�ϰ� �巡�� ���̸� : �Ķ���
//���콺 ���� KeyDown�ϰ� �巡�� ���̸� : ����Ÿ��

//https://www.glfw.org/
#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main(void)
{
	//glfw���̺귯�� �ʱ�ȭ
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(1.0f,0.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}