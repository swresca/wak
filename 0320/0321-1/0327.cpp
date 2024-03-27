//과제물 Lecture04_HW
//idel : 화면 검정색으로 clear
//마우스 오른쪽으로 key down하면 :빨간색
//마우스 오른쪽으로 key up하면 :원상복구
// //마우스 왼쪽로 key down하면 :녹색
//마우스 오른쪽으로 key up하면 :원상복구
// 마우스 오른쪽으로 key down 하고 드래그 중이면 :파란색
// 마우스 왼쪽 key down 하고 드래그 중이면 마젠타색  
 
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

        glfwSwapBuffers(window);
        
    }

    glfwTerminate();
    return 0;
}