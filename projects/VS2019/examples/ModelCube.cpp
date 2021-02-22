#include "ModelCube.h"

ModelCube::ModelCube(Vector3 position, float width, float height, float length, Color color)
{
	m_Position = position;
	m_Color = color;
	m_OriginalColor = m_Color;
	m_Model = LoadModelFromMesh(GenMeshCube(width, height, length));
	m_Height = height;
}

void ModelCube::Draw()
{
	DrawModel(m_Model, m_Position, 1.0f, m_Color);
	DrawCubeWires(m_Position, 2.0f, m_Height, 2.0f, MAROON);
}

bool ModelCube::Hits(Ray ray)
{
	RayHitInfo hitInfo = GetCollisionRayModel(ray, m_Model);
	m_Color = (hitInfo.hit ? GOLD : m_OriginalColor);
	return hitInfo.hit;
}




