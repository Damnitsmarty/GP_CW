#pragma once
#include <fstream>
#include <iostream>
#include <regex>
#include "Camera.h"
#include "GameObject.h"
#include "Display.h"
#include "Shader.h"

class Scene
{
public:
	Scene() {};
	Scene(Display * d);
	~Scene();
	void fromFile(const string& fileName);


	void Draw();

	Display* display;
	Shader* shader;
	Camera cam;
	std::vector<GameObject*> gos;
private:
	static string loadFile(const string& fileName);
	void parseScene(string text);

	static float nextFloat(string &text) {
		regex rFloat("[+-]?\\d+(?:\\.\\d+)?");
		smatch match;
		
		//if (!regex_search(text, match, rFloat)) return nullptr;
		regex_search(text, match, rFloat);

		float f = stof(match[0].str());

		text = match.suffix();
		return f;
	}
	
	static glm::vec3 nextVec3(string &text) {
		regex rVec3("\\(([+-]?\\d+(?:\\.\\d+)?),([+-]?\\d+(?:\\.\\d+)?),([+-]?\\d+(?:\\.\\d+)?)\\)");
		smatch match;

	
		//if (!regex_search(text, match, rVec3)) return nullptr;
		regex_search(text, match, rVec3);

		float x = stof(match[1].str());
		float y = stof(match[2].str());
		float z = stof(match[3].str());

		text = match.suffix();
		return glm::vec3(x, y, z);
	}
	static string nextString(string &text) {
		regex rString("\"(.*?)\"");
		smatch match;

		//if (!regex_search(text, match, rString)) return nullptr;
		regex_search(text, match, rString);

		string s = match[1].str();

		text = match.suffix();
		return s;
	}
};