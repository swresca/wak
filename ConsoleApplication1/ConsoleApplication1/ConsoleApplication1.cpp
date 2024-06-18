#include <GLFW/glfw3.h>
#include <iostream>

// 게임 윈도우 크기
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// 플레이어 크기
const float PLAYER_SIZE = 50.0f;

// 장애물 크기
const float OBSTACLE_SIZE = 50.0f;
const float OBSTACLE_SPEED = 200.0f;

// 점수
int score = 0;

// 플레이어 위치
float playerX = WINDOW_WIDTH / 4.0f;
float playerY = WINDOW_HEIGHT / 2.0f;

// 장애물 위치
float obstacleX = WINDOW_WIDTH;
float obstacleY = WINDOW_HEIGHT / 2.0f;

// 게임 오버 여부
bool gameOver = false;

// 키보드 입력 처리
void keyboardFunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_UP:
            playerY += PLAYER_SIZE;
            break;
        case GLFW_KEY_DOWN:
            playerY -= PLAYER_SIZE;
            break;
        case GLFW_KEY_LEFT:
            playerX -= PLAYER_SIZE;
            break;
        case GLFW_KEY_RIGHT:
            playerX += PLAYER_SIZE;
            break;
        }
    }
}

// 게임 오브젝트 그리기
void drawPlayer() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(playerX - PLAYER_SIZE / 2, playerY - PLAYER_SIZE / 2);
    glVertex2f(playerX + PLAYER_SIZE / 2, playerY - PLAYER_SIZE / 2);
    glVertex2f(playerX + PLAYER_SIZE / 2, playerY + PLAYER_SIZE / 2);
    glVertex2f(playerX - PLAYER_SIZE / 2, playerY + PLAYER_SIZE / 2);
    glEnd();
}

void drawObstacle() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(obstacleX - OBSTACLE_SIZE / 2, obstacleY - OBSTACLE_SIZE / 2);
    glVertex2f(obstacleX + OBSTACLE_SIZE / 2, obstacleY - OBSTACLE_SIZE / 2);
    glVertex2f(obstacleX + OBSTACLE_SIZE / 2, obstacleY + OBSTACLE_SIZE / 2);
    glVertex2f(obstacleX - OBSTACLE_SIZE / 2, obstacleY + OBSTACLE_SIZE / 2);
    glEnd();
}

// 충돌 감지
bool checkCollision() {
    float dx = playerX - obstacleX;
    float dy = playerY - obstacleY;
    float distance = std::sqrt(dx * dx + dy * dy);
    return distance < (PLAYER_SIZE + OBSTACLE_SIZE) / 2;
}

// 게임 로직 업데이트
void update(GLFWwindow* window) {
    if (!gameOver) {
        // 장애물 이동
        obstacleX -= OBSTACLE_SPEED * (1.0f / 60.0f);
        if (obstacleX < -OBSTACLE_SIZE) {
            obstacleX = WINDOW_WIDTH;
            obstacleY = rand() % (int)(WINDOW_HEIGHT - OBSTACLE_SIZE);
            score++;
        }

        // 충돌 감지
        if (checkCollision()) {
            gameOver = true;
        }

        // 화면 업데이트
        glClear(GL_COLOR_BUFFER_BIT);

        // 플레이어 및 장애물 그리기
        drawPlayer();
        drawObstacle();

        // 점수 표시
        glColor3f(1.0f, 1.0f, 1.0f);
        char scoreText[32];
        sprintf(scoreText, "Score: %d", score);
        glRasterPos2f(10.0f, WINDOW_HEIGHT - 20.0f);
        for (char* c = scoreText; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }

        // 게임 오버 메시지
        if (gameOver) {
            glColor3f(1.0f, 0.0f, 0.0f);
            glRasterPos2f(WINDOW_WIDTH / 2.0f - 100.0f, WINDOW_HEIGHT / 2.0f);
            for (char* c = "Game Over"; *c != '\0'; c++) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
            }
        }

        glfwSwapBuffers(window);
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dino Run", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyboardFunc);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);

    while (!glfwWindowShouldClose(window)) {
        update(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
