#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h"
#include "Scene.h"
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
	vector<Scene*> scenes;
	size_t activeScene;

	float counter;


	void initSystems();
	void processInput();
	void HandleKeyboardInput(SDL_KeyboardEvent e);
	void gameLoop();
	void drawGame();






};

