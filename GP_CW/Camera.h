#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct InputInfo {
	bool W, S, A, D, Space, Ctrl = false;
	int mouseMotionX, mouseMotionY = 0;
	InputInfo() {
		Reset();
	}
	void Reset() {
		W = S = A = D = Space = Ctrl = false;
		mouseMotionX = mouseMotionY = 0;
	}
};


struct Camera
{
public:
	Camera(){}

	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
		inputInfo.Reset();
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	/// <summary>
	///	Updates the position of the camera. 
	/// Should be called every frame.
	/// </summary>
	void UpdatePosition() {
		float amt = 0.05;

		glm::vec3 movement(
			(int)inputInfo.A - (int)inputInfo.D,
			(int)inputInfo.Space - (int) inputInfo.Ctrl,
			(int)inputInfo.W - (int)inputInfo.S);
		movement = movement * glm::vec3(amt);

		Move(movement);
		UpdateRotation();
	}


	void UpdateRotation() {

		float mvmt = 500.0;
		Pitch((float)inputInfo.mouseMotionY/mvmt);
		//inverting the yaw to simulate accurate head movement
		Yaw((float)inputInfo.mouseMotionX/-mvmt);


		//reset mouse motion after applying rotation!
		inputInfo.mouseMotionX = inputInfo.mouseMotionY = 0;
	}


	///<summary>
	/// Moves the camera by the specified amount.
	///</summary>
	///<param name="amt"> A vector3 representing the distance to move.</param>
	void Move(glm::vec3 amt) {
		//x,y,z

		//z
		pos += forward * amt.z;
		//x
		pos += glm::cross(up, forward) * amt.x;
		//y
		pos += up * amt.y;
	}

	

    void Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	void Yaw(float angle)
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, UP);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}
	InputInfo inputInfo;
protected:
private:

	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};


