#ifndef KEYPRESS_HPP
#define KEYPRESS_HPP

/*
	Handling keypress events as:
		Camera movement:
			W:		move camera forward
			A:		move camera left
			S:		move camera backwards
			D:		move camera right
			X:		move camera down
			SPACE:	move camera up
			8:		incrase camera movement speed
			9:		decrase camera movement speed
		Object Rotation:
			I:		rotates the object left on X axis
			K:		rotates the object right on X axis
			J:		rotates the object left on Y axis
			L:		rotates the object right on Y axis
			U:		rotates the object left on Z axis
			O:		rotates the object right on Z axis
			M:		incrases the speed
			N:		reduces the speed
		Polygon Mode:
			1: 		wireframe
			2:		points
			3:		filled
		Switching beteewen texture and color:
			C:		color mode
				4:	changing the value of R
				5:	changing the value of G
				6:	changing the value of B
			V:		texture mode
			B:		texture versions
				texture
				color
				mixture between texture and color
*/

#include "camera.hpp"
#include "headers.hpp"
#include "shader.hpp"

void keyPressHandler_Camera_wasdSpaceX(GLFWwindow *window, Camera &camera);
void keyPressHandler_Camera_Speed(GLFWwindow *window, Camera &camera);
void keyPressHandler_PolygonModes(GLFWwindow *window, Object &object);
void keyPressHandler_Color_OR_Texture(GLFWwindow *window, int &version, Object &object);
void keyPressHandler_SetColor(GLFWwindow *window, glm::vec3 &color);
void keyPressHandler_SetColorVersion(GLFWwindow *window, int &version, Object &object);
glm::mat4 keyPressHandler_ObjectCenterRotation(GLFWwindow *window, std::vector<float> &Triangles,
											   std::vector<float> &Squares, glm::mat4 &model);
glm::vec3 calculateCenter(const std::vector<float> &triangles);
void keyPressHandler_SetLight(GLFWwindow *window, Shader &shader, Object &object);

#endif