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
	//m_shader = new Shader("../res/shader");


	//load scenes from file
	scenes.push_back(new Scene(&_gameDisplay));
	scenes.back()->fromFile("../res/level1.txt");
	scenes.push_back(new Scene(&_gameDisplay));
	scenes.back()->fromFile("../res/level2.txt");
	//set active scene
	activeScene = 0;

}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		scenes[activeScene]->cam.UpdatePosition();
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
				scenes[activeScene]->cam.inputInfo.mouseMotionX = evnt.motion.xrel;
				scenes[activeScene]->cam.inputInfo.mouseMotionY = evnt.motion.yrel;
			}
			break;
		}
	}

}


///<summary>
/// Processes Keyboard Input events
///</summary>
///<param name="e"> The KeyboardEvent to process </param>
void MainGame::HandleKeyboardInput(SDL_KeyboardEvent e) {
	
	switch (e.keysym.sym) 
	{
		case SDLK_COMMA:
			//prev scene
			if (e.state == SDL_PRESSED) {
				if (activeScene > 0) activeScene--;
			}
			break;
		case SDLK_PERIOD:
			//next scene
			//exit if this was the last scene
			if (e.state == SDL_PRESSED) {
				if (activeScene < scenes.size() - 1) activeScene++;
				else _gameState = GameState::EXIT;
			}
			break;
		case SDLK_w:
			scenes[activeScene]->cam.inputInfo.W = (e.state == SDL_PRESSED);
			break;
		case SDLK_s:
			scenes[activeScene]->cam.inputInfo.S = (e.state == SDL_PRESSED);
			break;
		case SDLK_a:
			scenes[activeScene]->cam.inputInfo.A = (e.state == SDL_PRESSED);
			break;
		case SDLK_d:
			scenes[activeScene]->cam.inputInfo.D = (e.state == SDL_PRESSED);
			break;
		case SDLK_SPACE:
			scenes[activeScene]->cam.inputInfo.Space = (e.state == SDL_PRESSED);
			break;
		case SDLK_LCTRL:
			scenes[activeScene]->cam.inputInfo.Ctrl = (e.state == SDL_PRESSED);
			break;
		default:
			cout << e.keysym.sym << endl;
			break;
	}
}

void MainGame::drawGame(Shader* shader)
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	scenes[activeScene]->Draw();
	counter = counter + 0.01f;
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 