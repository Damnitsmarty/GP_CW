#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "GameObject.h"
enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	GameState _gameState;

	Display _gameDisplay;
	Shader* m_shader;
	Camera myCamera;
	std::vector<GameObject*> gos;

	float counter;


	void initSystems();
	void processInput();
	void HandleKeyboardInput(SDL_KeyboardEvent e);
	void gameLoop();
	void drawGame(Shader* shader);






};

