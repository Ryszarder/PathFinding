#include "Enemy.h"
#include "Input.h"

Enemy::Enemy()
{
	m_Enemies = new aie::Texture*[4];
	for (int i = 0; i < 4; ++i)
	{
		m_Enemies[i] = new aie::Texture("../bin/textures/Dice.png");
	}

	m_fPosX = 100;
	m_fPosY = 100;

	m_pPathfinder = new Pathfinder();

	m_bFollow = false;
}

Enemy::~Enemy()
{
	for (int i = 0; i < 4; i++)
	{
		delete m_Enemies[i];
	}
	delete[] m_Enemies;

	/*delete m_Enemies;
	m_Enemies = nullptr;*/

	delete m_pPathfinder;
	m_pPathfinder = nullptr;
}

void Enemy::Update(float fDeltaTime)
{
	aie::Input* m_Input = aie::Input::GetInstance();
}

void Enemy::Draw(aie::Renderer2D* pRenderer)
{
	for (int i = 0; i < 5; ++i)
	{
		pRenderer->DrawSprite(m_Enemies, m_fPosX, m_fPosY, 32, 32);
	}
	
}
