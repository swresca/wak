#include "Object.h"
#include <GLFW/glfw3.h>
#include <iostream>

float PIXEL_PER_MT = 0.0025f;

// 객체 배열
Object* objects[6];

// 바닥 높이 (픽셀 단위)
float floorY = -0.0025f * 300;

// 시간 측정용 변수
float lastTime = glfwGetTime();

// 키 입력 콜백 함수
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        Player* player = static_cast<Player*>(objects[0]);
        player->jump();
    }
}

int main() {
    // GLFW 초기화
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // GLFW 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // V-sync 활성화

    glClearColor(0.0f, 0.1176f, 0.39215f, 1.0f);

    // 객체 생성
    objects[0] = new Player(1.0f, 0.0f, 0.5f, 0.0f, 0.0f);
    objects[1] = new Floor();
    objects[2] = new EnemyBlock(1.0f, true, 0.3f, 0.0f, 0.0f, 0.0f);
    objects[3] = new EnemyBlock(1.0f, true, 0.5f, 0.0f, 0.0f, 0.0f);
    objects[4] = new EnemyBlock(1.0f, false, 0.7f, 0.0f, 0.0f, 0.0f);
    objects[5] = new EnemyBlock(1.0f, false, 0.9f, 0.0f, 0.0f, 0.0f);

    // 키 입력 콜백 등록
    glfwSetKeyCallback(window, keyCallback);

    // 메인 루프
    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        for (auto obj : objects) {
            obj->update(deltaTime, floorY);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        for (auto obj : objects) {
            obj->render();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 객체 삭제
    for (auto obj : objects) {
        delete obj;
    }

    // GLFW 종료
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}