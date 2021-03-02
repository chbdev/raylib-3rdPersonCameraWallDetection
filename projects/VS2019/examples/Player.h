#pragma once
#include <raymath.h>
#include <vector>
#include "ModelCube.h"

class Player
{
private:
	Vector3 m_Position;
	Camera* m_Camera;

public:

	//Debug
	Vector3 hitPos;
	Ray ray;
	bool storeHit;
	//end debug

	Player(Camera* camera);
	void Update(float deltaTime);
	void Draw(std::vector<ModelCube*>& columns);
};

