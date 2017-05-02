#include "Scene.h"


Scene::Scene(Display* d,Shader* s)
{
	this->display = d;
	this->shader = s;
}


Scene::~Scene()
{
	//MainGame's job
	//delete display;
	//delete shader;
}

void Scene::fromFile(const std::string& fileName)
{
	//read the file
	string text = loadFile(fileName);
	parseScene(text);
}

void Scene::Draw()
{
	for (int i = 0; i < gos.size(); i++)
	{
		gos[i]->Draw();
	}
}

string Scene::loadFile(const std::string & fileName)
{
	string text;
	ifstream file;
	file.open((fileName).c_str());
	if (file.is_open())
	{
		string line;
		while (file.good())
		{
			//#	file.get() also gets tabulations(\t) and new lines (\n,\r,etc)
			//#	which we don't need anyways
			//#	TODO: calculate performance using both ways
			
			//text += (char)file.get();


			file >> line;
			text += line;
		}
	}
	file.close();

	//remove all comments
	regex commentRegex("(?:\\{\\{.*?\\}\\})|\\");
	text = regex_replace(text, commentRegex, "");


	return text;
}

void Scene::parseScene(string text)
{
	//
	//	CAMERA
	//
	regex rCamExtract("CAM\\((.*?)\\);");
	regex rCamSettings("\\d+(?:\\.\\d+)?");
	smatch rMatch;

	if (regex_search(text, rMatch, rCamExtract)) {
		printf("Camera found. Extracting settings");
		string camSettings = rMatch[1].str();


		glm::vec3 camPos = nextVec3(camSettings);
		float camFOV = nextFloat(camSettings);
		float camNearClip = nextFloat(camSettings);
		float camFarClip = nextFloat(camSettings);

		//TODO:throw exceptions when settings are incomplete
		cam.initCamera(
			camPos,												//position
			camFOV,												//fov
			(float)display->getWidth() / display->getHeight(),	//aspect ratio (w/h)
			camNearClip,										//near clip plane
			camFarClip											//far clip plane
			);

	}
	else {
		//TODO: learn how to throw exceptions in general...
		printf("No camera in scene.");
		cam.initCamera(
			glm::vec3(0, 0, -5),										//position
			70.0f,														//fov
			(float)display->getWidth() / display->getHeight(),			//aspect ratio (w/h)
			0.01f,														//near clip plane
			1000.0f														//far clip plane
			);
	}

	//
	//	GAME OBJECTS
	//
	regex rGOExtract("GO\\((.*?)\\);");

	while (regex_search(text, rMatch, rGOExtract))
	{
		string GOSettings = rMatch[1].str();

		string GOName = nextString(GOSettings);
		string GOPathMesh = nextString(GOSettings);
		string GOPathTex = nextString(GOSettings);
		glm::vec3 GOPosition = nextVec3(GOSettings);
		glm::vec3 GORotation = nextVec3(GOSettings);
		glm::vec3 GOScale = nextVec3(GOSettings);

		gos.push_back(new GameObject(GOName.c_str(), GOPathMesh.c_str(), GOPathTex.c_str(), &cam, shader));
		gos.back()->transform.SetPos(GOPosition);
		gos.back()->transform.SetRot(GORotation);
		gos.back()->transform.SetScale(GOScale);

		text = rMatch.suffix();
	}

}
