#include "Texture.h"

GLuint tex::loadTexture(const char* path) {
  //Make a texture
  GLuint textureID;

  int textureWidth, textureHeight;

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  //GL_REPEAT for multiplication in fragment shader
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //Load SOIL image
  unsigned char* image = SOIL_load_image(path, &textureWidth, &textureHeight, 0, SOIL_LOAD_RGBA);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

  //Enable alpha

  //Make a mipmap
  glGenerateMipmap(GL_TEXTURE_2D);
  //Delete image since it's already made and stored in textureID
  SOIL_free_image_data(image);
  //Bind default texture
  glBindTexture(GL_TEXTURE_2D, 0);

  return textureID;
}

GLuint tex::loadCubemap(std::vector<const char*> faces)
{
	//Load a cubemap
	GLuint textureID;


	int textureWidth, textureHeight;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (GLuint i = 0; i < faces.size(); i++) {
		unsigned char* image = SOIL_load_image(faces[i], &textureWidth, &textureHeight, 0, SOIL_LOAD_RGB);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}

	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}
