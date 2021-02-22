#pragma once
#include <raymath.h>

class ModelCube
{
public: 
	ModelCube(Vector3 position, float width, float height, float length, Color color);
	void Draw();
	bool Hits(Ray ray);

	Vector3 m_Position;
private:
	Model m_Model;
	Color m_Color;
	Color m_OriginalColor;
	float m_Height;
};

