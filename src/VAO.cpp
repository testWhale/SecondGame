#include"VAO.h"

// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	// layout: 0 for vertex position, 1 for vertex color, etc.
	// numComponents: 3 for 3D position, 3 for RGB color, etc.
	// type: GL_FLOAT for float Compnt, GL_UNSIGNED_INT for unsigned int Compnt, etc.
	// stride: size of the whole vertex (aka. num of components * type) (e.g., 6 * sizeof(float) for 3D position) as we have x,y,z,r,g,b
	// offset: distance from the component in the buffer (e.g., 0 for position, 3 * sizeof(float) for color)
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}