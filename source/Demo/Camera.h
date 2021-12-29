#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

enum CameraMoveOption
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
public:
	// 相机的位置
	// 观察目标的位置
	// 世界向上的方向
	Camera(glm::vec3 cameraPosition, glm::vec3 targetPosition, glm::vec3 worldUp);
	Camera(glm::vec3 cameraPosition, float pitch, float yaw, glm::vec3 worldUp);
	~Camera();

public:
	glm::mat4 GetViewMatrix();  // 返回观察矩阵
	// 处理鼠标移动
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	// 处理键盘操作
	void ProcessKeyboard(CameraMoveOption direction, float deltaTime = 0.001f);
	// 处理滚轮操作
	void ProcessMouseScroll(float yoffset);

	float GetZoom() { return m_zoom; }

private:
	void UpdateCameraVectors();


public:
	float m_pitch = 0.0f;
	float m_yaw = -90.0f;

	float m_movementSpeed = 1.0f;      // 移动速度
	float m_mouseSensitivity = 0.001f;   // 鼠标灵敏度
	float m_zoom = 45.0f;               // 缩放

public:
	glm::vec3 m_position;  // 相机位置
	glm::vec3 m_forward;   // 相机前方向量
	glm::vec3 m_rihght;    // 相机右方
	glm::vec3 m_up;        // 相机上方
	glm::vec3 m_worldUp;   // 世界的上方方向
};

