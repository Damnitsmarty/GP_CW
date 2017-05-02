#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include "GameObject.h"
#include "Scene.h"
Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
}

MainGame::~MainGame()
{
	delete m_shader;
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	//init display
	_gameDisplay.initDisplay(1920.0,960.0);

	//load shader
	m_shader = new Shader("../res/shader");

	//load scene from file
	scene = Scene(&_gameDisplay, m_shader);
	scene.fromFile("../res/level1.txt");
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		scene.cam.UpdatePosition();
		drawGame(m_shader);
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			HandleKeyboardInput(evnt.key);
			break;
		case SDL_KEYUP:
			HandleKeyboardInput(evnt.key);
			break;
		case SDL_MOUSEMOTION:
			//check that left mouse button is pressed before handing values
			if (evnt.motion.state & SDL_BUTTON_LMASK) {
				scene.cam.inputInfo.mouseMotionX = evnt.motion.xrel;
				scene.cam.inputInfo.mouseMotionY = evnt.motion.yrel;
			}
			break;
		}
	}

}


///<summary>
/// Processes Keyboard Input events by updating Camera's movement modifiers
///</summary>
///<param name="e"> The KeyboardEvent to process </param>
void MainGame::HandleKeyboardInput(SDL_KeyboardEvent e) {

	switch (e.keysym.sym) 
	{
		case SDLK_w:
			scene.cam.inputInfo.W = (e.state == SDL_PRESSED);
			break;
		case SDLK_s:
			scene.cam.inputInfo.S = (e.state == SDL_PRESSED);
			break;
		case SDLK_a:
			scene.cam.inputInfo.A = (e.state == SDL_PRESSED);
			break;
		case SDLK_d:
			scene.cam.inputInfo.D = (e.state == SDL_PRESSED);
			break;
		case SDLK_SPACE:
			scene.cam.inputInfo.Space = (e.state == SDL_PRESSED);
			break;
		case SDLK_LCTRL:
			scene.cam.inputInfo.Ctrl = (e.state == SDL_PRESSED);
			break;
		default:
			break;
	}
}

void MainGame::drawGame(Shader* shader)
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	shader->Bind();
	scene.Draw();
	counter = counter + 0.01f;
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 