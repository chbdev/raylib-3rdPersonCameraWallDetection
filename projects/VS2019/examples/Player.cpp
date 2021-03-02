#include "Player.h"
#include <iostream>

Player::Player(Camera* camera) : m_Position(Vector3{ 0.0f, 1.0f, 0.0f })
{
	m_Camera = camera;
	storeHit = false;
	hitPos = Vector3{ 0.0f, 0.0f, 0.0f };
	ray = Ray{ Vector3{ 0.0f, 0.0f, 0.0f } , Vector3{ 1.0f, 0.0f, 0.0f } };
}

void Player::Update(float deltaTime)
{
	constexpr int SPEED = 4;
	if (IsKeyDown(KEY_W))
		m_Position.z += SPEED * deltaTime;
	if (IsKeyDown(KEY_A))
		m_Position.x += SPEED * deltaTime;
	if (IsKeyDown(KEY_S))
		m_Position.z -= SPEED * deltaTime;
	if (IsKeyDown(KEY_D))
		m_Position.x -= SPEED * deltaTime;

	if (IsKeyDown(KEY_F11))
	{
		storeHit = true;
	}

	m_Camera->target = m_Position; // Vector3Add(m_Position, Vector3{ 0.0f, 2.0f, -1.0f });
	UpdateCamera(m_Camera);	// Update camera
}

void Player::Draw(std::vector<ModelCube*>& columns)
{
	DrawCube(m_Position, 1.0f, 2.0f, 1.0f, ORANGE);
	DrawCube(Vector3Add(m_Position, Vector3{ 0.0f, 0.0f, 0.5f }), 0.5f, 0.5f, 0.5f, BLUE);

	Vector3 start = m_Camera->position;
	Vector3 end = m_Position;
	float lenght = Vector3Length(Vector3Subtract(end, start));

	Ray rayFromCameraToPlayer{ start, Vector3Subtract(end, start) };
	
	RayHitInfo info;
	bool hits = false;
	for (ModelCube* column : columns)
	{
		if (column->HitsAtLenght(rayFromCameraToPlayer, lenght, info))
		{
			if (storeHit)
			{
				hitPos = info.position;
				ray = rayFromCameraToPlayer;
				storeHit = false;
			}
			hits = true;
			break;
		}
	}
	DrawRay(rayFromCameraToPlayer, hits? RED:GREEN);
	
	DrawSphere(hitPos, 0.15f, BLUE);
	DrawRay(ray, RED);
}
