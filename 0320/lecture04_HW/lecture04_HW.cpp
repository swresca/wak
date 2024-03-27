#include <iostream>
#pragma comment(lib, "opengl32.lib")
#include <GLFW/glfw3.h>

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // 빨간색
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 검정색
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // 녹색
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 검정색
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 파랑색
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // 마젠타색
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    // glfw 라이브러리 초기화
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
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // 마우스를 먹게 만들어 준당 개꿀
        glfwPollEvents();

        // 버퍼를 초기화 시킨다.
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}