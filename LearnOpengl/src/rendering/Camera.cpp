#include "Camera.h"

void OpenGLCamera::Start()
{

}

void OpenGLCamera::Update()
{
	float sens = 0.1f;
	glm::vec2 mouseDelta = Input::GetMouseDelta() * sens;
	pitch -= mouseDelta.y;
	yaw += mouseDelta.x;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_Front = glm::normalize(front);

	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));

	glm::vec2 mov = Input::GetWASDVector();
	float delta = Time::GetTimeDelta();

	m_Position += mov.y * m_Right * 5.0f * delta;
	m_Position += mov.x * m_Front * 5.0f * delta;

	m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

OpenGLCamera::OpenGLCamera(glm::vec3 position, float startYaw, float startPitch) 
{
	glm::vec2 dimensions = Input::GetScreenDimensions();
	m_Projection = glm::perspective(glm::radians(70.0f), (float)800 / (float)600, 0.1f, 100.0f);
	m_WorldUp = m_Up;
}

glm::mat4 &OpenGLCamera::GetProjection()
{
	return m_Projection;
}

glm::mat4 &OpenGLCamera::GetView() 
{
	return m_View;
}
