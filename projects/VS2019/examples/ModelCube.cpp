#include "ModelCube.h"

#include <iostream>

ModelCube::ModelCube(Vector3 position, float width, float height, float length, Color color)
{
	m_Position = position;
	m_Color = color;
	m_OriginalColor = m_Color;
	m_Model = LoadModelFromMesh(GenMeshCube(width, height, length));
	m_Model.transform = MatrixTranslate(m_Position.x, m_Position.y, m_Position.z);
	m_Height = height;
}

void ModelCube::Draw()
{
	//DrawModel(m_Model, Vector3{ 0.0f,0.0f,0.0f }, 1.0f, m_Color);
	DrawCubeWires(m_Position, 2.0f, m_Height, 2.0f, BLACK);
}

bool ModelCube::HitsAtLenght(Ray ray, float lenght, RayHitInfo& outInfo)
{
	RayHitInfo hitInfo = GetCollisionRayModel(ray, m_Model);
	outInfo = hitInfo;
	
	float hitDistance = 0.0f;
	if (hitInfo.hit)
	{
		Vector3 hitPos = hitInfo.position;
		Vector3 origin = ray.position;
		hitDistance = Vector3Length(Vector3Subtract(hitPos, origin));
		//BUG @carlos - this if is needed because hitInfo.distance seems to not be working as expected
	}
	
	bool result = (hitInfo.hit/* && hitDistance <= lenght*/);
	m_Color = (result ? GOLD : m_OriginalColor);
	return result;
}




