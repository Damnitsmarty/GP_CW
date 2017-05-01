#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
//#include "camera.h"

struct Transform
{
public:
	///<summary>
	/// Initializes the Transform
	///</summary>
	///<param name="pos">Position of the transform</param>
	///<param name="rot">Rotation of the transform</param>
	///<param name="scale"> Scale of the transform</param>
	Transform(
		const glm::vec3& pos = glm::vec3(), 
		const glm::vec3& rot = glm::vec3(), 
		const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(pos);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

	/*inline glm::mat4 GetMVP(const Camera& camera) const
	{
		glm::mat4 VP = camera.GetViewProjection();
		glm::mat4 M = GetModel();

		return VP * M;//camera.GetViewProjection() * GetModel();
	}*/
	///<summary>Gets the Transform's position</summary>
	inline glm::vec3* GetPos() { return &pos; } //getters
	///<summary>Gets the Transform's rotation</summary>
	inline glm::vec3* GetRot() { return &rot; }
	///<summary>Gets the Transform's scale</summary>
	inline glm::vec3* GetScale() { return &scale; }

	///<summary>Sets the Transform's position</summary>
	inline void SetPos(glm::vec3& pos) { this->pos = pos; }
	///<summary>Sets the Transform's position</summary>
	inline void SetPos(float x, float y, float z) { this->pos = glm::vec3(x, y, z); }

	///<summary>Sets the Transform's rotation</summary>
	inline void SetRot(glm::vec3& rot) { this->rot = rot; }
	///<summary>Sets the Transform's rotation</summary>
	inline void SetRot(float x, float y, float z) { this->rot = glm::vec3(x, y, z); }

	///<summary>Sets the Transform's scale</summary>
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }
	///<summary>Sets the Transform's scale</summary>
	inline void SetScale(float x, float y, float z) { this->scale = glm::vec3(x, y, z); }

protected:
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};


