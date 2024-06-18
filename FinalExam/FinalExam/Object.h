#pragma once
#include "pch.h"

class Object {
public:
	float x, y;       // 중심 위치
	float vx, vy;     // 속도
	float SIZE = 50.0f * 0.0025f; // 물체 크기 (폭과 높이)

	Object(float x = 0, float y = 0, float vx = 0, float vy = 0)
		: x(x), y(y), vx(vx), vy(vy) {}

	virtual void update(float deltaTime, float floorY)
	{
		x += vx * deltaTime;
		y += vy * deltaTime;
	}

	virtual void render()
	{

	}

	virtual void OnCollisionEnter(Object& other)
	{

	}
};

class Player : public Object {
public:
	float mass;       // 질량
	float GRAVITY = 9.8f;  // 중력 상수
	float jumpSpeed = 5.0f;  // 점프 속도 (m/s)
	bool isJumping = false;  // 점프 중 여부

	Player(float mass, float x = 0, float y = 0, float vx = 0, float vy = 0)
		: Object(x, y, vx, vy), mass(mass) {}

	void update(float deltaTime, float floorY) override {
		if (isJumping) {
			vy = jumpSpeed; // 점프 속도 설정
			isJumping = false; // 점프 상태 해제
		}
		else {
			vy -= GRAVITY * deltaTime; // 중력 적용
		}

		x += vx * deltaTime;
		y += vy * deltaTime;

		// 바닥에 닿으면 위치와 속도 조정
		if (y - SIZE / 2 <= floorY) {
			y = floorY + SIZE / 2;
			vy = 0;
		}

		// OpenGL 좌표에 맞게 위치 조정
		x = std::max(-1.0f + SIZE / 2, std::min(1.0f - SIZE / 2, x));
		y = std::max(-1.0f + SIZE / 2, std::min(1.0f - SIZE / 2, y));
	}

	void render() override {
		float aspectRatio = 800.0f / 600.0f; // 가로 세로 비율

		float normalizedWidth = SIZE * aspectRatio;
		float normalizedHeight = SIZE;

		float borderWidth = 0.01f;

		// 테두리 사각형
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2f(x - normalizedHeight / 2 - borderWidth, y - normalizedWidth / 2 - borderWidth);
		glVertex2f(x + normalizedHeight / 2 + borderWidth, y - normalizedWidth / 2 - borderWidth);
		glVertex2f(x + normalizedHeight / 2 + borderWidth, y + normalizedWidth / 2 + borderWidth);
		glVertex2f(x - normalizedHeight / 2 - borderWidth, y + normalizedWidth / 2 + borderWidth);
		glEnd();

		// 내부 채우기 사각형
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex2f(x - normalizedHeight / 2, y - normalizedWidth / 2);
		glVertex2f(x + normalizedHeight / 2, y - normalizedWidth / 2);
		glVertex2f(x + normalizedHeight / 2, y + normalizedWidth / 2);
		glVertex2f(x - normalizedHeight / 2, y + normalizedWidth / 2);
		glEnd();
	}

	void jump() {
		if (!isJumping && y - SIZE / 2 <= 0.0f) { // 바닥에서만 점프 가능하도록 제한
			isJumping = true;
		}
	}

	void OnCollisionEnter(Object& other) override {
		// 충돌 처리
	}
};


class EnemyBlock : public Object {
public:
	float mass;
	bool isHigh; // 낮은지 높은지 여부

	EnemyBlock(float mass, bool isHigh, float x = 0, float y = 0, float vx = 0, float vy = 0)
		: Object(x, y, vx, vy), mass(mass), isHigh(isHigh) {}

	void update(float deltaTime, float floorY) override {
		// 장애물은 움직이지 않으므로 update()는 비워둡니다.
	}

	void render() override {
		float width = 0.0025f * 50; // 가로 길이

		// 장애물의 높이 설정
		float height = isHigh ? 0.0025f * 100.0f : 0.0025f * 300.0f;

		// 바닥에 붙어서 생성되도록 y 위치 설정
		float bottomY = -1.0f + 0.25f + height / 2.0f;
		y = bottomY;

		glColor3ub(0, 255, 0); // 녹색
		glBegin(GL_QUADS);
		glVertex2f(x - width / 2, y - height / 2);
		glVertex2f(x + width / 2, y - height / 2);
		glVertex2f(x + width / 2, y + height / 2);
		glVertex2f(x - width / 2, y + height / 2);
		glEnd();
	}

	void OnCollisionEnter(Object& other) override {
		// 충돌 처리
	}
};

class Floor : public Object {
public:
	void update(float deltaTime, float floorY) override {
		// 바닥은 움직이지 않으므로 update()는 비워둡니다.
	}

	void render() override {
		glColor3f(1.0f, 0.784f, 0.059f); // 황갈색
		glBegin(GL_QUADS);
		glVertex2f(-1.0f, -0.0025f * 300);  // (-400, -200)을 OpenGL 좌표로 변환
		glVertex2f(1.0f, -0.0025f * 300);   // (400, -200)을 OpenGL 좌표로 변환
		glVertex2f(1.0f, -0.0025f * 400);   // (400, -300)을 OpenGL 좌표로 변환
		glVertex2f(-1.0f, -0.0025f * 400);  // (-400, -300)을 OpenGL 좌표로 변환
		glEnd();
	}

	void OnCollisionEnter(Object& other) override {
		// 충돌 처리
	}
};


class Star : public Object {
public:
	void OnCollisionEnter(Object& other) override {
	}
};



//int PhysicsAABB(Object A, Object B)
//{
//	return 0;
//}