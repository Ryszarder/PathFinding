#include "Game2D.h"
#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "AgentTwo.h"
#include "Controller.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();

	// Create some textures for testing.
	m_font = new aie::Font("./font/consolas.ttf", 24);

	m_pPathfinder = new Pathfinder();

	//Creates the four agents and initalise them
	for (int i = 0; i < 4; ++i)
	{
		m_pAI[i] = new AgentTwo(m_pPathfinder, { 200, 200 });
	}
	
	//Creates the player and initalise it
	m_pControl = new Controller(m_pPathfinder, { 100, 100 });

	//Variable to keep track of when to close the game when all four agents are gone
	count = 0;
}

Game2D::~Game2D()
{
	//Delete the player
	delete m_pControl;

	//Delete all four agents
	delete m_pAI[0];
	delete m_pAI[1];
	delete m_pAI[2];
	delete m_pAI[3];

	//Delete the pathfinder
	delete m_pPathfinder;

	// Delete the renderer.
	delete m_2dRenderer;

	// Deleted the textures.
	delete m_font;
}

void Game2D::Update(float deltaTime)
{
	//If count equals 4
	if (count == 4)
	{
		//Close the game
		exit(0);
	}

	// Input example: Update the camera position using the arrow keys.
	aie::Input* input = aie::Input::GetInstance();

	float camPosX;
	float camPosY;

	m_2dRenderer->GetCameraPos(camPosX, camPosY);

	//// Exit the application if escape is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}

	//When left mouse button is click
	if (input->WasMouseButtonPressed(0))
	{
		//Find the mouse position on the game where clicked
		Vector2 mousePos = { input->GetMouseX(), input->GetMouseY() };

		//Get the node clicked on
		GraphNode* pNode = m_pPathfinder->GetNodeByPos(mousePos);

		//If click on a node
		if (pNode)
		{
			//Set node to blocked creating a blue node that the agent can't move into
			pNode->m_bBlocked = true;
		}

		//Draw the new node
		Draw();
	}

	//If right mouse button is click
	if (input->WasMouseButtonPressed(1))
	{
		//Find where on the game the mouse position clicked on
		Vector2 mousePos = { input->GetMouseX(), input->GetMouseY() };

		//Get the node clicked on
		GraphNode* pNode = m_pPathfinder->GetNodeByPos(mousePos);

		//If clicked on a node
		if (pNode)
		{
			//Set blocked to false getting rid of the blue node
			pNode->m_bBlocked = false;
		}

		//Draw new node
		Draw();
	}

	//If the key E was pressed
	if (input->WasKeyPressed(aie::INPUT_KEY_E))
	{
		//Get the player position when the key is pressed
		Vector2 ConPos = m_pControl->GetPos();

		//Get the node clicked on
		GraphNode* pNode = m_pPathfinder->GetNodeByPos(ConPos);

		//if clicked on node
		if (pNode)
		{
			//Set Attack true turning into a red node that will delete agent when crossed
			pNode->m_bAttack = true;
		}

		//Draw new node
		Draw();
	}

	//If key Q was pressed
	if (input->WasKeyPressed(aie::INPUT_KEY_Q))
	{
		//Get the player position when the key is pressed
		Vector2 ConPos = m_pControl->GetPos();

		//Get the node clicked on
		GraphNode* pNode = m_pPathfinder->GetNodeByPos(ConPos);

		//If clicked on node
		if (pNode)
		{
			//Set Attack to false turing red back to normal green node
			pNode->m_bAttack = false;
		}

		//Draw new node
		Draw();
	}

	//For loop to run through all the agents
	for (int i = 0; i < 4; ++i)
	{
		//If agent doesn't equal null 
		if (m_pAI[i] != nullptr)
		{
			//Get agent position on the game
			Vector2 AgentPos = m_pAI[i]->GetPos();

			//Get the node the agent is on
			GraphNode* pNode = m_pPathfinder->GetNodeByPos(AgentPos);

			//If the node Attack equals true
			if (pNode->m_bAttack == true)
			{
				//Agent equals null
				m_pAI[i] = nullptr;

				//Increase the count by 1
				count++;
			}

		}

		//If agent doesn't equal null
		if(m_pAI[i] != nullptr)
		{
			//Run the Update function in the agentTwo cpp
			m_pAI[i]->Update(deltaTime);
		}
	}
	
	//Run the Controll update function
	m_pControl->Update(deltaTime);
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	//Render the pathfinder
	m_pPathfinder->Render(m_2dRenderer);
	
	//For loop to run through the agents
	for (int i = 0; i < 4; ++i)
	{
		//If agent doesn't eqaul null
		if (m_pAI[i] != nullptr)
		{
			//Draw the agent
			m_pAI[i]->Draw(m_2dRenderer);
		}
	}

	//Draw the player
	m_pControl->Draw(m_2dRenderer);
	
	// Draw some text.
	float windowHeight = (float)application->GetWindowHeight();
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	m_2dRenderer->DrawText2D(m_font, fps, 15.0f, windowHeight - 32.0f);
	
	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}