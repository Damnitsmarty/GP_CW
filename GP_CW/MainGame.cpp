#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
    Mesh* mesh1();
	Mesh* mesh2();
	Mesh* mesh3();
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
	_gameDisplay.initDisplay(); 
	
	//load shader
	m_shader = new Shader("../res/shader");
	//load models
	mesh1.loadModel("../res/Rock1.obj");
	mesh2.loadModel("../res/monkey3.obj");
	mesh3.loadModel("../res/notebook.obj");

	//load textures
	m_texture1 = new Texture("../res/rock.jpg"); //load texture
	m_texture2 = new Texture("../res/bricks.jpg"); //load texture
	m_texture3 = new Texture("../res/Water.jpg"); //load texture


	myCamera.initCamera(
		glm::vec3(0, 0, -5),										//position
		70.0f,														//fov
		(float)_gameDisplay.getWidth() / _gameDisplay.getHeight(),  //aspect ratio (w/h)
		0.01f,														//near clip plane
		1000.0f														//far clip plane
		);

	//initialize counter
	counter = 0.0f;
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame(m_shader);
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


void MainGame::drawGame(Shader* shader)
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	

	shader->Bind();
	//Draw rock model
	transform.SetPos(glm::vec3(5.0, 0.0, 3.0));
	transform.SetRot(glm::vec3(0.0, counter * -2, 0.0));
	transform.SetScale(glm::vec3(0.8, 0.8, 0.8));
	shader->Update(transform, myCamera);

	m_texture1->Bind(0);
	mesh1.draw();


	//Draw monkey model
	transform.SetPos(glm::vec3(-5.0, 0.0, 3.0));
	transform.SetRot(glm::vec3(0.0, counter * 2, 0.0));
	transform.SetScale(glm::vec3(0.8,0.8,0.8));
	shader->Update(transform, myCamera);

	m_texture2->Bind(0);
	mesh2.draw();

	//Draw notebook model
	transform.SetPos(glm::vec3(0.0, 0.0, 3.0));
	transform.SetRot(glm::vec3(0.0, counter * 2, 0.0));
	transform.SetScale(glm::vec3(0.8, 0.8, 0.8));
	shader->Update(transform, myCamera);

	m_texture3->Bind(0);
	mesh3.draw();

	counter = counter + 0.01f;
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 