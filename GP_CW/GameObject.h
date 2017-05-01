#pragma once
#include "transform.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "Shader.h"
class GameObject
{
public:
	GameObject(string name,const char* modelname, const char* texname, 
		Camera* cam, Shader* shader)
	{
		this->name = name;
		this->cam = cam;
		this->shader = shader;

		transform = Transform();
		//reset the transform
		this->transform.SetPos(glm::vec3(0, 0, 0));
		this->transform.SetRot(glm::vec3(0, 0, 0));
		this->transform.SetScale(glm::vec3(1, 1, 1));


		mesh.loadModel(modelname);
		tex = new Texture(texname);
	}


	
	~GameObject() {
	};


	inline void Draw() {
		shader->Update(transform,*cam);

		tex->Bind(0);
		mesh.draw();
	}
	string name;
	Texture* tex;
	Transform transform;
	Mesh mesh;
	Camera* cam;
	Shader* shader;
};

