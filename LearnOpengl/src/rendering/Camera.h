#pragma once
#include "perhapsPch.h"
#include "utils/Input.h"

class OpenGLCamera : Loopable
{
	glm::mat4 m_Projection = glm::mat4(1);
	glm::mat4 m_View = glm::mat4(1);
	glm::vec3 m_Position = glm::vec3(0,0,0);
	glm::vec3 m_Front = glm::vec3(0,0,0);
	glm::vec3 m_Up = glm::vec3(0,1,0);
	glm::vec3 m_Right = glm::vec3(0,0,0);
	glm::vec3 m_WorldUp = glm::vec3(0,1,0);
	float pitch = 0, yaw = 0.0f;

	public:
	void Update() override;
	void Start() override;
	OpenGLCamera(glm::vec3 position = glm::vec3(0, 0, 0), float startYaw = 0, float startPitch = 0);
	glm::mat4 &GetProjection();
	glm::mat4 &GetView();
};