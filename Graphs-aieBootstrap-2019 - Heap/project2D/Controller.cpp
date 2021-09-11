#include "Controller.h"
#include "Pathfinder.h"
#include "Input.h"

//Constructor
Controller::Controller(Pathfinder* pPathefinder, Vector2 v2Position)
{
	m_pPathfinder = pPathefinder;
	m_v2Position = v2Position;
}

//Destructor
Controller::~Controller()
{
}

//Update
void Controller::Update(float DeltaTime)
{
	aie::Input* m_input = aie::Input::GetInstance();

	//If W key is pressed
	if (m_input->WasKeyPressed(aie::INPUT_KEY_W))
	{
		//Add 20 to position.y
		m_v2Position.y += 20.0f;
	}

	//If S key is pressed
	if (m_input->WasKeyPressed(aie::INPUT_KEY_S))
	{
		//Minus 20 to position.y
		m_v2Position.y -= 20.0f;
	}

	//If A key is pressed
	if (m_input->WasKeyPressed(aie::INPUT_KEY_A))
	{
		//Minus 20 to position.x
		m_v2Position.x -= 20.0f;
	}

	//If D key is pressed
	if (m_input->WasKeyPressed(aie::INPUT_KEY_D))
	{
		//Add 20 to position.x
		m_v2Position.x += 20.0f;
	}

	//Set the position of the controller
	SetPos(m_v2Position);
}

//Draw
void Controller::Draw(aie::Renderer2D* pRenderer)
{
	//Draw the box that the controller controls
	pRenderer->DrawBox(m_v2Position.x, m_v2Position.y, 15, 15);
}

//Set position
void Controller::SetPos(Vector2 v2Position)
{
	//Set the vector position the same as the position passed in
	m_v2Position = v2Position;
}

//Get position
Vector2 Controller::GetPos()
{
	//Give the position when called
	return m_v2Position;
}
