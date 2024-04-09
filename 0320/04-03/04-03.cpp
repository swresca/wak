
#pragma comment(lib,"Opengl32.lib")
#include <iostream>
#include <GLFW/glfw3.h>


void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error : " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int render()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.5f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.5f, 0.0f);
    glEnd();
    return 0;
}

int main(void)
{
    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "swresca", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 검정색으로 클리어
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw code here
            
        render();
        
       glfwSwapBuffers(window);

    }

    glfwTerminate();
    return 0;
}