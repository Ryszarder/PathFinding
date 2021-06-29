#pragma once
#include "Renderer2D.h"
#include "Texture.h"
#include "Pathfinder.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer);

	enum State
	{
		STATE_IDLE,
		STATE_FOLLOW
	};

private:
	aie::Texture** m_Enemies;
	aie::Renderer2D* m_2dRender;
	std::vector<Vector2> m_vPath;

	Pathfinder* m_pPathfinder;

	State m_eState = State::STATE_IDLE;

	float m_fPosX;
	float m_fPosY;

	bool m_bFollow;
};

