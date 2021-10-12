#pragma once

#include <core.hpp>

#define UNSUPPORTED 0
#define SUPPORTED 1
#define EXTENSION 2 

namespace GLHelper {

	GLFWwindow* window();

	void vertexAttribute( GLint index, GLint length, GLenum type, GLsizei stride, GLsizei offset, GLsizei size, GLboolean normalize = GL_FALSE );
	void getError( const char* name = nullptr );

	int getSizeOf( GLenum thing );

	bool init(int, int, const char*);
	void frame();

	int feature( int major, int minor, GLenum extension );

	// screenshot utilities
	byte* capture( int*, int* );
	void screenshot( const std::string& path );

	ShaderProgram* loadShaderProgram( std::string );

}

