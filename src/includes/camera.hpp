#ifndef CAMERA_H
#define CAMERA_H

#include "headers.hpp"

/*
	Controls zooming, rotating the camera with mouse,
	moving the camera on x, y and z based on the direction
	of the camera with wasdqe buttons.
*/

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 25.0f;

const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
   public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float Yaw;
	float Pitch;
	float MovementSpeed;
	float changeSpeed = 2.0f;
	float MouseSensitivity;
	float Zoom;

	float nearPlane = 0.1f;
	float farPlane = 1500.0f;

	float lastX = WINDOW_WIDTH / 2.0f;
	float lastY = WINDOW_HEIGHT / 2.0f;
	bool firstMouse = true;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw,
		   float pitch);
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);
	void fps(Camera &camera);
	glm::mat4 getViewMatrix();

   private:
	void updateCameraVectors();
};
#endif