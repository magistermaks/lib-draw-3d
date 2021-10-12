#pragma once

#include <core.hpp>

struct VertexAttribute {

	const int length;
	const GLenum type;
	const GLsizei size;
	const GLboolean normalize;

	VertexAttribute( int length, GLenum type, GLsizei size, GLboolean normalize = GL_FALSE );

};

class VertexConsumer {

	private:

		GLuint vbo, vao;

		FastBuffer<float> buffer;

	public:

		// primitive info
		const GLenum primitive;
		const int length;

		VertexConsumer( GLenum primitive, int length );
		VertexConsumer( VertexConsumer&& consumer );
		~VertexConsumer();

		template< class... Args, class = trait::are_types_equal< float, Args... > >
		void vertex( Args... args ) {
			this->buffer.insert( args... );
		}

		void clear() {
			this->buffer.clear();
		}

		// prepare and bind OpenGL buffers
		void bind();
		long count();
		void submit();
		void shrink();

};

class VertexConsumerProvider {

	private:

		GLenum primitive = GL_TRIANGLES;
		int length = 0;
		std::vector<VertexAttribute> attributes;

		void apply();

	public:

		void setPrimitive( GLenum primitive );
		void attribute( int size );
		void attribute( VertexAttribute attr );

		VertexConsumer get();
	
};

