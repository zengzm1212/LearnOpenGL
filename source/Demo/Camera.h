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
	// �����λ��
	// �۲�Ŀ���λ��
	// �������ϵķ���
	Camera(glm::vec3 cameraPosition, glm::vec3 targetPosition, glm::vec3 worldUp);
	Camera(glm::vec3 cameraPosition, float pitch, float yaw, glm::vec3 worldUp);
	~Camera();

public:
	glm::mat4 GetViewMatrix();  // ���ع۲����
	// ��������ƶ�
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	// ������̲���
	void ProcessKeyboard(CameraMoveOption direction, float deltaTime = 0.001f);
	// ������ֲ���
	void ProcessMouseScroll(float yoffset);

	float GetZoom() { return m_zoom; }

private:
	void UpdateCameraVectors();


public:
	float m_pitch = 0.0f;
	float m_yaw = -90.0f;

	float m_movementSpeed = 1.0f;      // �ƶ��ٶ�
	float m_mouseSensitivity = 0.001f;   // ���������
	float m_zoom = 45.0f;               // ����

public:
	glm::vec3 m_position;  // ���λ��
	glm::vec3 m_forward;   // ���ǰ������
	glm::vec3 m_rihght;    // ����ҷ�
	glm::vec3 m_up;        // ����Ϸ�
	glm::vec3 m_worldUp;   // ������Ϸ�����
};

