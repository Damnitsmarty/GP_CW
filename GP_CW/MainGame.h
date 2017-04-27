#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:
	Shader* m_shader;
	Texture* m_texture1;
	Texture* m_texture2;
	Texture* m_texture3;


	void initSystems();
	void processInput();
	void HandleKeyboardInput(SDL_KeyboardEvent e);
	void gameLoop();
	void drawGame(Shader* shader);

	Display _gameDisplay;
	GameState _gameState;

	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;

	Camera myCamera;

	float counter;


};

