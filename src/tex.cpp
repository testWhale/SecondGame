
//#include "tex.h"
//#include "stb/stb_image.h"
//
//// Constructor that generates a Elements Buffer Object and links it to indices
//Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
//{
//	// Assigns the type of the texture ot the texture object
//	type = texType;
//
//	// Stores the width, height, and the number of color channels of the image
//	int widthImg, heightImg, numColCh;
//	// Flips the image so it appears right side up
//	stbi_set_flip_vertically_on_load(true);
//	// Reads the image from a file and stores it in bytes
//	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
//	if (bytes)
//	{
//		// Generates an OpenGL texture object
//		glGenTextures(1, &ID);
//		// Assigns the texture to a Texture Unit
//		glActiveTexture(slot);
//		glBindTexture(texType, ID);
//
//		// Configures the type of algorithm that is used to make the image smaller or bigger
//		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
//		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//		// Configures the way the texture repeats (if it does at all)
//		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//		// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
//		 float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
//		 glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
//		GLenum format = (numColCh == 4) ? GL_RGBA : GL_RGB;
//		// Assigns the image to the OpenGL Texture object
//		glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
//		// Generates MipMaps
//		glGenerateMipmap(texType);
//	}
//	else
//	{
//		std::cout << "Failed to load texture " << image << std::endl;
//	}
//
//	// Deletes the image data as it is already in the OpenGL Texture object
//	stbi_image_free(bytes);
//
//	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
//	glBindTexture(texType, 0);
//}
//
//// Binds the EBO
//void Texture::texUnit(Shader& shader,const char* uniform, GLuint unit)
//{
//	// create uniform
//	GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
//	// Shader needs to be activated before changing the value of a uniform
//	shader.use();
//	glUniform1f (tex0Uni, unit);
//}
//// Unbinds the EBO
//void Texture::Bind()
//{
//	// Bind the texture so OpenGL knows to use it
//	glBindTexture(type, ID);
//}
//
//
//// Unbinds the EBO
//void Texture::Unbind()
//{
//	// Bind the texture so OpenGL knows to use it
//	glBindTexture(type, 0);
//}
//
//// Deletes the EBO
//void Texture::Delete()
//{
//	glDeleteTextures(1, &ID);
//}





//unsigned int texture1;
//glGenTextures(1, &texture1);
//
//// Define Texture Unit
//glActiveTexture(GL_TEXTURE1);
//// Bind the texture 
//glBindTexture(GL_TEXTURE_2D, texture1);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//// set the texture wrapping/filtering options (on the currently bound texture object)
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//
//data = stbi_load("awesomeface.jpg", &width, &height, &nrChannels, 0);
//if (data)
//{
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//	glGenerateMipmap(GL_TEXTURE_2D);
//}
//else
//{
//	std::cout << "Failed to load texture" << std::endl;
//}
//// Clear the image from memory after using it
//stbi_image_free(data);
//glBindTexture(GL_TEXTURE_2D, 0);
//
//// create uniform
//GLuint tex1Uni = glGetUniformLocation(shaderProgram.ID, "textureUni2");
