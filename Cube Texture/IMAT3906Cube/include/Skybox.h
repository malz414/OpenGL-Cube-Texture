#ifndef SKYBOX_H
#define SKYBOX_H


#include <stb_image.h>

#include "Camera.h"

#include "Shader.h"

class Skybox {

public:

	Skybox();
	void createSkyBox();
	void renderSkybox(Shader& skyboxShader);


private:

	void loadCubeMapTextures();
	unsigned int loadCubemap(std::vector<std::string> faces);
	void createVAO();

	std::vector<std::string> faces;
	unsigned int skyBoxTexObj;
	unsigned int skyBoxVAO;

 };

#endif