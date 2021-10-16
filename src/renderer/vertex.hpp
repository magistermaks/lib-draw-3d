#pragma once

#include <core.hpp>

enum struct Consumer : unsigned int {
	VERTEX,
	INSTANCE,
		
	COUNT
};

struct VertexAttribute {

	const int length;
	const GLenum type;
	const GLsizei size;
	const GLboolean normalize;
	const GLuint divisor;

	VertexAttribute( int length, GLenum type, GLsizei size, GLboolean normalize = GL_FALSE, GLuint divisor = 0 );

};

class VertexConsumer {

	public:

		GLuint vbo = 0, ibo = 0, vao;

		FastBuffer<float> vertex_buffer, instance_buffer;

		// allow VertexConsumerProvider to access private
		// fields so that it can initilize VAO pointers
		friend class VertexConsumerProvider;

	public:

		// primitive info
		const GLenum primitive;
		const int vertex_length, instance_length;

		VertexConsumer( GLenum primitive, int vertex_length , int instance_length );
		VertexConsumer( VertexConsumer&& consumer );
		~VertexConsumer();

		template< class... Args, class = trait::are_types_equal< float, Args... > >
		void vertex( Args... args ) {
			this->vertex_buffer.insert( args... );
		}

		void vertex( VertexConsumer& consumer ) {
			this->vertex_buffer.from(consumer.vertex_buffer);
		}

		void clearVertex() {
			this->vertex_buffer.clear();
		}

		template< class... Args, class = trait::are_types_equal< float, Args... > >
		void instance( Args... args ) {
			this->instance_buffer.insert( args... );
		}

		void instance( VertexConsumer& consumer ) {
			this->instance_buffer.from(consumer.instance_buffer);
		}

		void clearInstance() {
			this->instance_buffer.clear();
		}

		// prepare and bind OpenGL buffers
		void bind();
		long count();
		void submit();
		void shrink();

};

class VertexConsumerProvider {

	private:

		struct Profile {
			int length = 0;
			std::vector<VertexAttribute> attributes;
		};

		GLenum primitive = GL_TRIANGLES;
		Profile profiles[(int) Consumer::COUNT];
		int profile = (int) Consumer::VERTEX;

		void apply(int& index, Consumer profile);

	public:
	
		void setPrimitive( GLenum primitive );
		void attribute( int size );
		void attribute( VertexAttribute attr );

		void target(Consumer profile);

		VertexConsumer get();
	
};

