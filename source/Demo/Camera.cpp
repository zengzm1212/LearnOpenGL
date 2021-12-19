#include "Camera.h"
#include <glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 targetPosition, glm::vec3 worldUp)
{
	m_worldUp = worldUp;
	m_position = cameraPosition;
	m_forward = glm::normalize(targetPosition - m_position);  // 观察物体的方向
	m_rihght = glm::normalize(glm::cross(m_worldUp, m_forward));    // 相机的右方 = 世界坐标上方 × 相机前方
	m_up = glm::normalize(glm::cross(m_forward, m_rihght)); // 相机的上方 = 相机的前方 × 相机的右方
}

Camera::Camera(glm::vec3 cameraPosition, float pitch, float yaw, glm::vec3 worldUp)
{
	m_position = cameraPosition;
	m_worldUp = worldUp;
	m_pitch = pitch;
	m_yaw = yaw;

	// 球面坐标系的转换。pith 和 yaw 是角度
	UpdateCameraVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	// m_forward 虽然是单位向量，但是 m_position + m_forward 指向的是目标的相对位置，所以最终结果还是对的
	// 最终返回的是观察矩阵
	return glm::lookAt(m_position, m_position + m_forward, m_worldUp);
}


void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	// 控制鼠标精度
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw += xoffset;
	m_pitch -= yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (m_pitch > 89.0f)
			m_pitch = 89.0f;
		if (m_pitch < -89.0f)
			m_pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}

void Camera::ProcessKeyboard(CameraMoveOption direction, float deltaTime)
{
	float velocity = m_movementSpeed * deltaTime;
	if (direction == CameraMoveOption::FORWARD)
		m_position += m_forward * velocity;
	if (direction == CameraMoveOption::BACKWARD)
		m_position -= m_forward * velocity;
	if (direction == CameraMoveOption::LEFT)
		m_position -= m_rihght * velocity;
	if (direction == CameraMoveOption::RIGHT)
		m_position += m_rihght * velocity;
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (m_zoom < 1.0f)
		m_zoom = 1.0f;
	if (m_zoom > 65.0f)
		m_zoom = 65.0f;
	m_zoom -= yoffset;
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = glm::cos(m_pitch) * glm::sin(m_yaw);
	front.y = glm::sin(m_pitch);   // 世界坐标上方
	front.z = glm::cos(m_pitch) * glm::cos(m_yaw);
	m_forward = glm::normalize(front);

	// also re-calculate the Right and Up vector
	m_rihght = glm::normalize(glm::cross(m_worldUp, m_forward));
	m_up = glm::normalize(glm::cross(m_forward, m_rihght));
}