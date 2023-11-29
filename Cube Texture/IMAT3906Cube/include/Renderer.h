#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Shader.h"
#include "Camera.h"
#include "normalMapper.h"


class Renderer {

public:

	Renderer(unsigned int sW, unsigned int sH);
	void renderScene(Shader& shader, Shader& floorShader, Shader& skyboxShader, Camera camera);
	void renderQuad(Shader& shader, unsigned int& textureObj);
	void renderQuad(Shader& shader, unsigned int& textureObj, unsigned int& tex);
	void renderLights(Shader& lightShader, Camera camera);
	void renderCubes(Shader& shader);
	void drawLights(Shader& shader);
	void renderFloor(Shader& shader);
//	unsigned int  quadVAO, quadVBO;
private:

	void loadTextureFiles();
	unsigned int loadTexture(char const* path);


	void createCube();
	void createFloor();
	void createQuad();

	unsigned int cubeVAO, floorVAO, cubeVBO, cubeEBO, floorVBO, floorEBO, quadVAO, quadVBO;

	unsigned int screenW, screenH;

	unsigned int cubeDiffuse, cubeSpecular, cubeNM, cubeDisp, floorDiffuse, floorSpecular, floorNM, floorDM;


	const float floorSize = 5.0f;
	const float floorLevel = -2.0f;

	const glm::vec3 cubeColor = glm::vec3(1.0, 0.4, 0.4);
	const glm::vec3 floorColor = glm::vec3(1.0, 0.3, 0.3);

 };

#endif