#include "Game2D.h"

#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Player.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();

	// Create some textures for testing.
	m_font = new aie::Font("./font/consolas.ttf", 24);

	m_pPathfinder = new Pathfinder();
}

Game2D::~Game2D()
{
	// Deleted the textures.
	delete m_font;

	// Delete the renderer.
	delete m_2dRenderer;

	delete m_pPathfinder;
}

void Game2D::Update(float deltaTime)
{

	// Input example: Update the camera position using the arrow keys.
	aie::Input* input = aie::Input::GetInstance();
	float camPosX;
	float camPosY;

	m_2dRenderer->GetCameraPos(camPosX, camPosY);

	if (input->IsKeyDown(aie::INPUT_KEY_W))
		camPosY += 500.0f * deltaTime;

	if (input->IsKeyDown(aie::INPUT_KEY_S))
		camPosY -= 500.0f * deltaTime;

	if (input->IsKeyDown(aie::INPUT_KEY_A))
		camPosX -= 500.0f * deltaTime;

	if (input->IsKeyDown(aie::INPUT_KEY_D))
		camPosX += 500.0f * deltaTime;

	m_2dRenderer->SetCameraPos(camPosX, camPosY);

	// Exit the application if escape is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}

	if (input->WasMouseButtonPressed(0))
	{
		Vector2 mousePos = { input->GetMouseX(), input->GetMouseY() };
		GraphNode* pNode = m_pPathfinder->GetNodeByPos(mousePos);

		if (pNode)
		{
			pNode->m_bBlocked = true;
		}

		//Draw();
	}

	if (input->WasMouseButtonPressed(1))
	{
		Vector2 mousePos = { input->GetMouseX(), input->GetMouseY() };
		GraphNode* pNode = m_pPathfinder->GetNodeByPos(mousePos);

		if (pNode)
		{
			pNode->m_bBlocked = false;
		}

		//Draw();
	}
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	m_pPathfinder->Render(m_2dRenderer);

	//GraphNode* node = m_pPathfinder->GetNodeByPos({ 33, 33 });
	//m_2dRenderer->DrawCircle(node->m_v2Position.x, node->m_v2Position.y, 10);

	std::vector<Vector2> path;
	Vector2 start = { 60, 60 };
	Vector2 end = { 800, 60 };
	//Vector2 end = { 800, 60 };
	m_pPathfinder->AStarPath(start, end, path);

	for (int i = 0; i < path.size(); ++i)
	{
		m_2dRenderer->DrawCircle(path[i].x, path[i].y, 10);
	}
	
	// Draw some text.
	float windowHeight = (float)application->GetWindowHeight();
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	m_2dRenderer->DrawText2D(m_font, fps, 15.0f, windowHeight - 32.0f);
	//m_2dRenderer->DrawText2D(m_font, "Arrow keys to move.", 15.0f, windowHeight - 64.0f);
	//m_2dRenderer->DrawText2D(m_font, "WASD to move camera.", 15.0f, windowHeight - 96.0f);
	//m_2dRenderer->DrawText2D(m_font, "Press ESC to quit!", 15.0f, windowHeight - 128.0f);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}
