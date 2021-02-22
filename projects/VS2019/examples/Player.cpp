#include "Player.h"
#include <iostream>

Player::Player(Camera* camera) : m_Position(Vector3{ 0.0f, 1.0f, 0.0f })
{
	m_Camera = camera;
}

void Player::Update(float deltaTime)
{
	if (IsKeyDown(KEY_W))
		m_Position.z += 2 * deltaTime;
	if (IsKeyDown(KEY_A))
		m_Position.x += 2 * deltaTime;
	if (IsKeyDown(KEY_S))
		m_Position.z -= 2 * deltaTime;
	if (IsKeyDown(KEY_D))
		m_Position.x -= 2 * deltaTime;

	m_Camera->target = m_Position; // Vector3Add(m_Position, Vector3{ 0.0f, 2.0f, -1.0f });
	UpdateCamera(m_Camera);	// Update camera
}

void Player::Draw(std::vector<ModelCube*>& columns)
{
	DrawCube(m_Position, 1.0f, 2.0f, 1.0f, ORANGE);
	DrawCube(Vector3Add(m_Position, Vector3{ 0.0f, 0.0f, 0.5f }), 0.5f, 0.5f, 0.5f, BLUE);

	Vector3 start = m_Camera->position;
	Vector3 end = m_Position;
	Ray rayFromCameraToPlayer{ start, Vector3Subtract(end, start) };

	Vector3 startToEnd = Vector3Subtract(end, start);
	Vector3 dire = Vector3Normalize(startToEnd);
	float l = Vector3Length(startToEnd);
	float dl = l / 4.0f;
	
	for (int i = 1; i < 3; i++)
	{
		Vector3 pos = Vector3Add(start, Vector3Scale(dire, dl * i));
		float radius = 0.15f * i;
		DrawSphereWires(pos, radius, 10,10, i == 1 ? GREEN : RED);
	}

	DrawLine3D(Vector3Add(m_Camera->position, Vector3{ 0.01f,0.0f,0.0f }), m_Position, BLUE);
	std::cout << m_Camera->position.x << "," << m_Camera->position.y << "," << m_Camera->position.z << "," << std::endl;

	DrawSphere(start, 0.5f, BLUE);

	RayHitInfo info;
	bool hits = false;
	for (ModelCube* column : columns)
	{
		DrawLine3D(m_Position, column->m_Position, RED);
		
		if (column->Hits(rayFromCameraToPlayer))
		{
			hits = true;
			break;
		}
	}
	DrawRay(rayFromCameraToPlayer, hits? RED:GREEN);
}
