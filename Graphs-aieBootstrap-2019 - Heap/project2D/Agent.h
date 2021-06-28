#pragma once
#include "Renderer2D.h"
#include "Texture.h"

class Agent
{
public:
	Agent();
	~Agent();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);

private:
	aie::Texture* m_texture;

	int i = 0;

	float m_posX;
	float m_posY;
};

