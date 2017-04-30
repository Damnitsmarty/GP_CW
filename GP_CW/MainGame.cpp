#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include "GameObject.h"

Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
}

MainGame::~MainGame()
{
	delete m_texture1;
	delete m_texture2;
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
	_gameDisplay.initDisplay(); 
	
	//init camera
	myCamera.initCamera(
		glm::vec3(0, 0, -5),										//position
		70.0f,														//fov
		(float)_gameDisplay.getWidth() / _gameDisplay.getHeight(),  //aspect ratio (w/h)
		0.01f,														//near clip plane
		1000.0f														//far clip plane
		);

	//load shader
	m_shader = new Shader("../res/shader");

	//load GameObjects
	gos.push_back(GameObject("../res/monkey3.obj", "../res/rock.jpg", &myCamera, m_shader));
	//gos.back().init("../res/monkey3.obj", "../res/rock.jpg", &myCamera, m_shader);
	gos.back().transform.SetPos(5, 0, 3);

	gos.push_back(GameObject("../res/monkey3.obj", "../res/rock.jpg", &myCamera, m_shader));
	//gos.back().init("../res/monkey3.obj", "../res/rock.jpg", &myCamera, m_shader);
	gos.back().transform.SetPos(0, 0, 3);

	gos.push_back(GameObject("../res/monkey3.obj", "../res/rock.jpg", &myCamera, m_shader));
	//gos.back().init("../res/monkey3.obj", "../res/rock.jpg", &myCamera, m_shader);
	gos.back().transform.SetPos(-5, 0, 3);
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		myCamera.UpdatePosition();
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
				printf("%i %i\n", evnt.motion.xrel, evnt.motion.yrel);
				myCamera.inputInfo.mouseMotionX = evnt.motion.xrel;
				myCamera.inputInfo.mouseMotionY = evnt.motion.yrel;
			}
			else {
				myCamera.inputInfo.mouseMotionX = 0;
				myCamera.inputInfo.mouseMotionY = 0;
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
			myCamera.inputInfo.W = (e.state == SDL_PRESSED);
			break;
		case SDLK_s:
			myCamera.inputInfo.S = (e.state == SDL_PRESSED);
			break;
		case SDLK_a:
			myCamera.inputInfo.A = (e.state == SDL_PRESSED);
			break;
		case SDLK_d:
			myCamera.inputInfo.D = (e.state == SDL_PRESSED);
			break;
		case SDLK_SPACE:
			myCamera.inputInfo.Space = (e.state == SDL_PRESSED);
			break;
		case SDLK_LCTRL:
			myCamera.inputInfo.Ctrl = (e.state == SDL_PRESSED);
			break;
		default:
			break;
	}
}

void MainGame::drawGame(Shader* shader)
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	

	shader->Bind();


	/*for (std::vector<GameObject>::iterator it = gos.begin(); it < gos.end(); it++) {
		it->Draw();
	}*/
	gos[0].Draw();
	////Draw rock model
	//transform.SetPos(glm::vec3(5.0, 0.0, 3.0));
	//transform.SetRot(glm::vec3(0.0, counter * -2, 0.0));
	//transform.SetScale(glm::vec3(0.8, 0.8, 0.8));
	//shader->Update(transform, myCamera);

	//m_texture1->Bind(0);
	//mesh1.draw();


	////Draw monkey model
	//transform.SetPos(glm::vec3(-5.0, 0.0, 3.0));
	//transform.SetRot(glm::vec3(0.0, counter * 2, 0.0));
	//transform.SetScale(glm::vec3(0.8,0.8,0.8));
	//shader->Update(transform, myCamera);

	//m_texture2->Bind(0);
	//mesh2.draw();

	////Draw notebook model
	//transform.SetPos(glm::vec3(0.0, 0.0, 3.0));
	//transform.SetRot(glm::vec3(0.0, counter * 2, 0.0));
	//transform.SetScale(glm::vec3(0.8, 0.8, 0.8));
	//shader->Update(transform, myCamera);

	//m_texture3->Bind(0);
	//mesh3.draw();


	counter = counter + 0.01f;
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 