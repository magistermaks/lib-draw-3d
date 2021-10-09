#pragma once

#include <include/external.hpp>
#include <include/forward.hpp>
#include <util/buffer.hpp>

template< typename T >
class StorageBuffer {

	private:

		GLuint ssbo;
		int binding;
		
		FastBuffer<T> buffer;

	public:

		StorageBuffer( int binding ) {
			glGenBuffers(1, &ssbo);
			this->binding = binding;
		}

		StorageBuffer( StorageBuffer&& buffer ) : ssbo(buffer.ssbo), binding(buffer.binding), buffer(std::move(buffer.buffer)) {
			buffer.ssbo = 0;
		}

		~StorageBuffer() {
			glDeleteBuffers(1, &ssbo);
		}

		void push( const T& value ) {
			this->buffer.insert(value);
		}

		T& get( int index ) {
			return this->buffer.read(index);
		}

		void remove( int index ) {
			this->buffer.remove(index);
		}

		void clear() {
			this->buffer.clear();
		}

		// prepare and bind OpenGL buffers
		void bind() {
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, this->binding, this->ssbo);
		}

		void submit() {
			this->bind();

			glBufferData(GL_SHADER_STORAGE_BUFFER, this->buffer.size(), this->buffer.data(), GL_DYNAMIC_DRAW);
		}

};

