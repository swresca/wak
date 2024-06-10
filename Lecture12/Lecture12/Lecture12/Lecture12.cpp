#include <GLFW/glfw3.h>
#include <iostream>

// 윈도우 크기
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// 공룡 구조체
struct Dino {
    float x, y;
    float width, height;
    float velocityX, velocityY;
    bool isJumping;
};

// 땅 구조체
struct Ground {
    float y;
    float height;
};

// 공룡 초기화
Dino dino = { 100, 100, 50, 50, 0, 0, false };


// 땅 초기화
Ground ground = { 10, 10 }; // 땅의 y 좌표와 높이


// 점프 상수
const float JUMP_STRENGTH = 500.0f;
const float MOVE_SPEED = 200.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !dino.isJumping) {
        dino.velocityY = JUMP_STRENGTH;
        dino.isJumping = true;
    }

    if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        dino.velocityX = MOVE_SPEED;
    }

    if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        dino.velocityX = -MOVE_SPEED;
    }
}

void update(float deltaTime) {
    // 중력 적용
    const float GRAVITY = -312.5f; // 중력 가속도
    dino.velocityY += GRAVITY * deltaTime;
    dino.y += dino.velocityY * deltaTime;

    // 좌우 이동
    dino.x += dino.velocityX * deltaTime;

    // 땅과 충돌 검사
    if (dino.y <= ground.y) {
        dino.y = ground.y;
        dino.isJumping = false;
        dino.velocityY = 0;
    }

    // 화면 경계 검사
    if (dino.x < 0) {
        dino.x = 0;
    }
    else if (dino.x + dino.width > WINDOW_WIDTH) {
        dino.x = WINDOW_WIDTH - dino.width;
    }
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 공룡 렌더링 (흰색)
    glColor3f(1.0f, 1.0f, 1.0f); // 흰색 설정
    glBegin(GL_QUADS);
    glVertex2f(dino.x, dino.y);
    glVertex2f(dino.x + dino.width, dino.y);
    glVertex2f(dino.x + dino.width, dino.y + dino.height);
    glVertex2f(dino.x, dino.y + dino.height);
    glEnd();

    // 땅 렌더링 (초록색)
    glColor3f(0.0f, 1.0f, 0.0f); // 초록색 설정
    glBegin(GL_QUADS);
    glVertex2f(0, ground.y);
    glVertex2f(WINDOW_WIDTH, ground.y);
    glVertex2f(WINDOW_WIDTH, ground.y + ground.height);
    glVertex2f(0, ground.y + ground.height);
    glEnd();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dino Run", nullptr, nullptr);
    if (!window) {
        std::cerr << "윈도우 생성 실패" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // 뷰포트 설정
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float previousTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window)) {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        update(deltaTime);
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
    