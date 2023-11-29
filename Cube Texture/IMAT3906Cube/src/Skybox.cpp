#include "Skybox.h"

Skybox::Skybox(){

}


void Skybox::createSkyBox(){
	loadCubeMapTextures();
	createVAO();
}

void Skybox::renderSkybox(Shader& shader) {
	shader.use();
	glDepthMask(GL_FALSE);
	glBindVertexArray(skyBoxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTexObj);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}

void Skybox::loadCubeMapTextures()
{
	faces.push_back("..\\resources\\TropicalSunnyDay_px.jpg");
	faces.push_back("..\\resources\\TropicalSunnyDay_nx.jpg");

	faces.push_back("..\\resources\\TropicalSunnyDay_py.jpg");
	faces.push_back("..\\resources\\TropicalSunnyDay_ny.jpg");

	faces.push_back("..\\resources\\TropicalSunnyDay_pz.jpg");
	faces.push_back("..\\resources\\TropicalSunnyDay_nz.jpg");

	skyBoxTexObj = loadCubemap(faces);
}  
unsigned int Skybox::loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);



	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++) {
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);
				std::cout << "Loaded texture at path: " << faces[i] << " widht " << width << " id " << textureID << std::endl;
				stbi_image_free(data);
			}
			else {
				std::cout << "CubeMap Failed to load at path " << faces[i] << std::endl;
				stbi_image_free(data);
			}



	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void Skybox::createVAO(){
float skyboxVertices[] = {
            // positions          
-10.0f, 10.0f, -10.0f,
-10.0f, -10.0f, -10.0f,
10.0f, -10.0f, -10.0f,
10.0f, -10.0f, -10.0f,
10.0f, 10.0f, -10.0f,
-10.0f, 10.0f, -10.0f,

-10.0f, -10.0f, 10.0f,
-10.0f, -10.0f, -10.0f,
-10.0f, 10.0f, -10.0f,
-10.0f, 10.0f, -10.0f,
-10.0f, 10.0f, 10.0f,
-10.0f, -10.0f, 10.0f,

10.0f, -10.0f, -10.0f,
10.0f, -10.0f, 10.0f,
10.0f, 10.0f, 10.0f,
10.0f, 10.0f, 10.0f,
10.0f, 10.0f, -10.0f,
10.0f, -10.0f, -10.0f,

-10.0f, -10.0f, 10.0f,
-10.0f, 10.0f, 10.0f,
10.0f, 10.0f, 10.0f,
10.0f, 10.0f, 10.0f,
10.0f, -10.0f, 10.0f,
-10.0f, -10.0f, 10.0f,

-10.0f, 10.0f, -10.0f,
10.0f, 10.0f, -10.0f,
10.0f, 10.0f, 10.0f,
10.0f, 10.0f, 10.0f,
-10.0f, 10.0f, 10.0f,
-10.0f, 10.0f, -10.0f,

-10.0f, -10.0f, -10.0f,
-10.0f, -10.0f, 10.0f,
10.0f, -10.0f, -10.0f,
10.0f, -10.0f, -10.0f,
-10.0f, -10.0f, 10.0f,
10.0f, -10.0f, 10.0f
		};
		unsigned VBO; 
		glGenVertexArrays(1, &skyBoxVAO);
		glBindVertexArray(skyBoxVAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
}