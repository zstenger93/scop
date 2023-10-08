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
		Polygon Mode:
			1: 		wireframe
			2:		points
			3:		filled
*/

#include "camera.hpp"
#include "headers.hpp"

void keyPressHandler_Camera(GLFWwindow *window, RenderMode &renderMode, Camera &camera);
glm::mat4 keyPressHandler_ObjectCenterRotation(GLFWwindow *window, std::vector<float> &Triangles,
											   std::vector<float> &Squares, glm::mat4 &model);
glm::vec3 calculateCenter(const std::vector<float> &triangles);

#endif