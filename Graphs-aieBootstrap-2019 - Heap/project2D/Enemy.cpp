#include "Enemy.h"
#include "Input.h"

Enemy::Enemy()
{
	m_Enemies = new aie::Texture("../bin/textures/Dice.png");

	m_fPosX = 100;
	m_fPosY = 100;

	m_pPathfinder = new Pathfinder();

	m_bFollow = false;
}

Enemy::~Enemy()
{
	delete m_Enemies;
	m_Enemies = nullptr;

	delete m_pPathfinder;
	m_pPathfinder = nullptr;
}

void Enemy::Update(float fDeltaTime)
{
	aie::Input* m_Input = aie::Input::GetInstance();
}

void Enemy::Draw(aie::Renderer2D* pRenderer)
{
		pRenderer->DrawSprite(m_Enemies, m_fPosX, m_fPosY, 32, 32);
}
