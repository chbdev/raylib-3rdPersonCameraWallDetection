#pragma once
#include <raymath.h>

class ModelCube
{
public: 
	ModelCube(Vector3 position, float width, float height, float length, Color color);
	void Draw();
	bool HitsAtLenght(Ray ray, float lenght, RayHitInfo& outInfo);

	Vector3 m_Position;
private:
	Model m_Model;
	Color m_Color;
	Color m_OriginalColor;
	float m_Width;
	float m_Height;
	float m_Length;
};

