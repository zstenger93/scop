#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "camera.hpp"
#include "headers.hpp"
#include "text.hpp"

class Object {
   public:
	Mtl mtl;									  // material file content
	Text text;									  // for text drawing to screen
	int polyCount;								  // counted from file
	glm::mat4 model;							  // used for shader calculations
	std::vector<Uv> uv;							  // vt aka uv coordinates
	int textureType = 0;						  // switching between textures
	unsigned int texture;						  // texture used for the object
	bool hasSlash = false;						  // flag for type of the object file
	std::string windowName;						  // first 'o' from obj file
	glm::vec3 lightSourcePos;					  // pos of light
	std::vector<Vertex> vertices;				  // triangle ad square coordinates
	std::vector<char *> textures;				  // all textures saved here
	RenderMode renderMode = FILLED;				  // default, hotkey available
	std::vector<glm::vec3> normals;				  // vn aka normals for light calculations
	std::vector<std::vector<int> > faces;		  // contains each from the obj file
	std::vector<std::vector<int> > uv_index;	  // indexes for uv coordinates from each face
	std::vector<std::vector<Vertex> > triangles;  // contains all shapes for now
	std::vector<float> Triangles, unpreaparedSquares, Squares;	// converting squares to triangles
	GLuint VAO_triangles, VBO_triangles, normalVBO;				// vertex arrays and buffers
	std::chrono::high_resolution_clock::time_point start_time;
	std::chrono::high_resolution_clock::time_point end_time;
	std::chrono::duration<double> frame_duration;
	double frame_time;
	int fps_count;
	std::string fps;
};

void drawKeyBindingsPanel();
void cleanUp(Object &object);
void initObject(Object &object);
void createVaoVbo(Object &object);
void initIMGUI(GLFWwindow *window);
void saveTextures(Object &object, char **argv);
void drawInfoPanel(Object &object, glm::vec3 &color);
void renderText(GLFWwindow *window, Object &object, glm::vec3 &color);

#endif