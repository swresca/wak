#pragma once
#include "pch.h"

class Object {
public:
	float x, y;       // �߽� ��ġ
	float vx, vy;     // �ӵ�
	float SIZE = 50.0f * 0.0025f; // ��ü ũ�� (���� ����)

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
	float mass;       // ����
	float GRAVITY = 9.8f;  // �߷� ���
	float jumpSpeed = 5.0f;  // ���� �ӵ� (m/s)
	bool isJumping = false;  // ���� �� ����

	Player(float mass, float x = 0, float y = 0, float vx = 0, float vy = 0)
		: Object(x, y, vx, vy), mass(mass) {}

	void update(float deltaTime, float floorY) override {
		if (isJumping) {
			vy = jumpSpeed; // ���� �ӵ� ����
			isJumping = false; // ���� ���� ����
		}
		else {
			vy -= GRAVITY * deltaTime; // �߷� ����
		}

		x += vx * deltaTime;
		y += vy * deltaTime;

		// �ٴڿ� ������ ��ġ�� �ӵ� ����
		if (y - SIZE / 2 <= floorY) {
			y = floorY + SIZE / 2;
			vy = 0;
		}

		// OpenGL ��ǥ�� �°� ��ġ ����
		x = std::max(-1.0f + SIZE / 2, std::min(1.0f - SIZE / 2, x));
		y = std::max(-1.0f + SIZE / 2, std::min(1.0f - SIZE / 2, y));
	}

	void render() override {
		float aspectRatio = 800.0f / 600.0f; // ���� ���� ����

		float normalizedWidth = SIZE * aspectRatio;
		float normalizedHeight = SIZE;

		float borderWidth = 0.01f;

		// �׵θ� �簢��
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2f(x - normalizedHeight / 2 - borderWidth, y - normalizedWidth / 2 - borderWidth);
		glVertex2f(x + normalizedHeight / 2 + borderWidth, y - normalizedWidth / 2 - borderWidth);
		glVertex2f(x + normalizedHeight / 2 + borderWidth, y + normalizedWidth / 2 + borderWidth);
		glVertex2f(x - normalizedHeight / 2 - borderWidth, y + normalizedWidth / 2 + borderWidth);
		glEnd();

		// ���� ä��� �簢��
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex2f(x - normalizedHeight / 2, y - normalizedWidth / 2);
		glVertex2f(x + normalizedHeight / 2, y - normalizedWidth / 2);
		glVertex2f(x + normalizedHeight / 2, y + normalizedWidth / 2);
		glVertex2f(x - normalizedHeight / 2, y + normalizedWidth / 2);
		glEnd();
	}

	void jump() {
		if (!isJumping && y - SIZE / 2 <= 0.0f) { // �ٴڿ����� ���� �����ϵ��� ����
			isJumping = true;
		}
	}

	void OnCollisionEnter(Object& other) override {
		// �浹 ó��
	}
};


class EnemyBlock : public Object {
public:
	float mass;
	bool isHigh; // ������ ������ ����

	EnemyBlock(float mass, bool isHigh, float x = 0, float y = 0, float vx = 0, float vy = 0)
		: Object(x, y, vx, vy), mass(mass), isHigh(isHigh) {}

	void update(float deltaTime, float floorY) override {
		// ��ֹ��� �������� �����Ƿ� update()�� ����Ӵϴ�.
	}

	void render() override {
		float width = 0.0025f * 50; // ���� ����

		// ��ֹ��� ���� ����
		float height = isHigh ? 0.0025f * 100.0f : 0.0025f * 300.0f;

		// �ٴڿ� �پ �����ǵ��� y ��ġ ����
		float bottomY = -1.0f + 0.25f + height / 2.0f;
		y = bottomY;

		glColor3ub(0, 255, 0); // ���
		glBegin(GL_QUADS);
		glVertex2f(x - width / 2, y - height / 2);
		glVertex2f(x + width / 2, y - height / 2);
		glVertex2f(x + width / 2, y + height / 2);
		glVertex2f(x - width / 2, y + height / 2);
		glEnd();
	}

	void OnCollisionEnter(Object& other) override {
		// �浹 ó��
	}
};

class Floor : public Object {
public:
	void update(float deltaTime, float floorY) override {
		// �ٴ��� �������� �����Ƿ� update()�� ����Ӵϴ�.
	}

	void render() override {
		glColor3f(1.0f, 0.784f, 0.059f); // Ȳ����
		glBegin(GL_QUADS);
		glVertex2f(-1.0f, -0.0025f * 300);  // (-400, -200)�� OpenGL ��ǥ�� ��ȯ
		glVertex2f(1.0f, -0.0025f * 300);   // (400, -200)�� OpenGL ��ǥ�� ��ȯ
		glVertex2f(1.0f, -0.0025f * 400);   // (400, -300)�� OpenGL ��ǥ�� ��ȯ
		glVertex2f(-1.0f, -0.0025f * 400);  // (-400, -300)�� OpenGL ��ǥ�� ��ȯ
		glEnd();
	}

	void OnCollisionEnter(Object& other) override {
		// �浹 ó��
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