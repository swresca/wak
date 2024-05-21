#include <iostream>
#include <GLFW/glfw3.h>
#include <random>
#include <cmath>
#pragma comment(lib, "Opengl32.lib")


void errorCallback(int error, const char* description)
{
	std::cerr << "\033[1;31mGLFW Error: " << description << "\033[0m" << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int initialize()
{

	return 0;
}

int release()
{
	return 0;
}

int update()
{
	return 0;
}

float M_PI = 3.141592f;

void drawCircle(float centerX, float centerY, float radius, int numSegments, int red, int green, int blue) {
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(red, green, blue);  
	glVertex2f(centerX, centerY);
	for (int i = 0; i <= numSegments; ++i) {
		float angle = 2.0f * M_PI * float(i) / float(numSegments);
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		glVertex2f(centerX + x, centerY + y);
	}
	glEnd();
}

void drawEllipse(float centerX, float centerY, float radius, int numSegments, int red, int green, int blue) {
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(red, green, blue);  
	glVertex2f(centerX, centerY);
	float angleInRadians = 45.0f * M_PI / 360.0f;
	for (int i = 0; i <= numSegments; ++i) {
		float angle = 2.0f * M_PI * float(i) / float(numSegments);
		float x = radius * cosf(angle);
		float y = radius * sinf(angle) / 4;
		glVertex2f(centerX + x, centerY + y);
	}

	glEnd();
}

void drawCircleOutline(float centerX, float centerY, float radius, int numSegments, float lineWidth) {
	glLineWidth(lineWidth);  
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.5f, 0.0f);  
	for (int i = 0; i <= numSegments; ++i) {
		float angle = 2.0f * M_PI * float(i) / float(numSegments);
		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		glVertex2f(centerX + x, centerY + y);
	}
	glEnd();
	glLineWidth(1.0f);  
}

void drawRectangle(float centerX, float centerY, float length)
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(91, 155, 213);
	glVertex2f(centerX + (length / 2), centerY + (length / 2));
	glVertex2f(centerX - (length / 2), centerY + (length / 2));
	glVertex2f(centerX - (length / 2), centerY - (length / 2));
	glVertex2f(centerX + (length / 2), centerY - (length / 2));
	glEnd();
}

void drawRectangleOutline(float centerX, float centerY, float length, float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(centerX + (length / 2), centerY + (length / 2));
	glVertex2f(centerX - (length / 2), centerY + (length / 2));
	glVertex2f(centerX - (length / 2), centerY - (length / 2));
	glVertex2f(centerX + (length / 2), centerY - (length / 2));
	glEnd();
	glLineWidth(1.0f);
}

void drawStar()
{
	glColor3ub(255, 242, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 30);
	glVertex2f(-7, 10);
	glVertex2f(7, 10);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-7, 10);
	glVertex2f(-28, 10);
	glVertex2f(-11, -4);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-11, -4);
	glVertex2f(-17, -24);
	glVertex2f(0, -12);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(0, -12);
	glVertex2f(17, -24);
	glVertex2f(11, -4);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(11, -4);
	glVertex2f(28, 10);
	glVertex2f(7, 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(7, 10);
	glVertex2f(-7, 10);
	glVertex2f(-11, -4);
	glVertex2f(0, -12);
	glVertex2f(11, -4);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(7, 10);
	glVertex2f(0, 30);
	glVertex2f(-7, 10);
	glVertex2f(-28, 10);
	glVertex2f(-11, -4);
	glVertex2f(-17, -24);
	glVertex2f(0, -12);
	glVertex2f(17, -24);
	glVertex2f(11, -4);
	glVertex2f(28, 10);
	glVertex2f(7, 10);
	glEnd();
}

void render(float rotangle)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(rotangle, 0, 0, 1);
	drawCircle(0, 0, 180, 180, 255, 217, 102);
	drawCircleOutline(0, 0, 180, 180, 3.0f);
	drawCircle(-90, 0, 70, 50, 255, 230, 153);
	glRotatef(45, 0, 0, 1);
	drawEllipse(0, -163, 50, 50, 255, 192, 0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(-rotangle, 0, 0, 1);

	glRotatef(rotangle / 2, 0, 0, 1);
	glTranslatef(400, 0, 0);
	glRotatef(rotangle * 3, 0, 0, 1);
	drawRectangle(0, 0, 100);
	drawRectangleOutline(0, 0, 100, 2.0f);
	glRotatef(-rotangle * 3, 0, 0, 1);
	glRotatef(rotangle * 10, 0, 0, 1);
	glTranslatef(140, 0, 0);
	glRotatef(rotangle * 10, 0, 0, 1);
	drawStar();
	glRotatef(-rotangle * 10, 0, 0, 1);
	glRotatef(-rotangle / 2, 0, 0, 1);
	glTranslatef(-540, 0, 0);
	glRotatef(-rotangle * 10, 0, 0, 1);


}

int main(void)
{
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(1280, 720, "Rfdfsfsa", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);
	double rd = 0.0f;
	initialize();
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapInterval(1);
		glViewport(0, 0, 1280, 720);  // 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 1280, 0, 720, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(1280 / 2, 720 / 2, 0);

		glfwPollEvents();

		update();
		render(rd);

		rd += 0.0133333f * 12.0f;


		glfwSwapBuffers(window);
	}

	release();

	glfwTerminate();
	return 0;

}