#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

// 상수 선언
const double pixel_size = 0.1; // 픽셀 한 개의 크기 (미터 단위)
const double max_jump_height = 2.0; // 최대 점프 높이 (미터 단위)
const double mass = 40.0; // 질량 (킬로그램 단위)
const double gravity = 9.8; // 중력가속도 (미터/초^2 단위)

// 최대 점프 높이를 픽셀 단위로 변환
int max_jump_height_pixels = static_cast<int>(max_jump_height / pixel_size);

// 중력이 가하는 힘 계산
double force_gravity = mass * gravity;

// 힘을 계산하여 각 픽셀 당 중력에 의한 힘을 구함
double force_per_pixel = force_gravity / max_jump_height_pixels;

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 그래픽 시각화
    glColor3f(1.0, 0.0, 0.0); // 빨간색으로 설정
    glBegin(GL_QUADS);
    glVertex2f(-0.5, 0.0); // 왼쪽 아래 꼭지점
    glVertex2f(-0.5, max_jump_height_pixels); // 왼쪽 위 꼭지점
    glVertex2f(0.5, max_jump_height_pixels); // 오른쪽 위 꼭지점
    glVertex2f(0.5, 0.0); // 오른쪽 아래 꼭지점
    glEnd();

    glfwSwapBuffers(window);
}

int main() {
    GLFWwindow* window;

    /* GLFW 라이브러리 초기화 */
    if (!glfwInit())
        return -1;

    /* 윈도우 생성 */
    window = glfwCreateWindow(800, 800, "Gravity Simulation", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* 현재 윈도우 컨텍스트로 설정 */
    glfwMakeContextCurrent(window);

    /* OpenGL 초기화 */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    /* 렌더링 루프 */
    while (!glfwWindowShouldClose(window)) {
        /* 렌더링 */
        drawScene();

        /* 이벤트 핸들링 */
        glfwPollEvents();
    }

    /* GLFW 종료 */
    glfwTerminate();

    return 0;
}
