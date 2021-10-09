#pragma once

#include "trait.hpp"
#include "logger.hpp"

template< typename T >
class FastBuffer {

	private:

		T* buffer;
		int pos;
		int length;

	protected:

		void push( T value ) {
			this->buffer[ this->pos ++ ] = value;
		}

		template< typename... Args, typename = trait::are_types_equal< T, Args... > >
		void push( T first, Args... args ) {
			this->push(first);
			this->push(args...);
		}

	public:

		FastBuffer( int size = 16 );
		FastBuffer( FastBuffer&& );
		~FastBuffer();

		// copy buffer into a new array and return pointer
		T* copy();

		// get pointer to internal continous buffer
		T* data();

		// get internal buffer size in bytes
		int size();

		// check if this buffer is empty
		bool empty();
		
		// get number of elements in this buffer
		int count();

		// get current maximum capacity
		int capacity();

		// clear this buffer
		void clear();
		
		// ensure that `count` elements can be inserted
		void reserve( int count );

		// get reference of element at `index` to buffer element
		T& read( int index );

		// write `value` into buffer at `index`
		void write( int index, T value );

		// remove element at `index` from buffer
		void remove( int index );

		// insert `value` into the buffer
		void insert( T value );

		// insert `array` into buffer
		void insert( T* array, int length );

		// insert multiple elements into buffer
		template< typename... Args, typename = trait::are_types_equal< T, Args... > >
		void insert( T first, Args... args ) {
			this->reserve( 1 + sizeof...(args) );
			this->push(first);
			this->push(args...);
		}

};

template< typename T >
FastBuffer<T>::FastBuffer( int length ) {
	this->pos = 0;
	this->length = length;
	this->buffer = (T*) malloc(length * sizeof(T));
}

template< typename T >
FastBuffer<T>::FastBuffer( FastBuffer<T>&& buffer ) {
	this->pos = buffer.pos;
	this->length = buffer.length;
	this->buffer = buffer.buffer;

	buffer.buffer = nullptr;
}

template< typename T >
FastBuffer<T>::~FastBuffer() {
	if( this->buffer != nullptr ) {
		free(this->buffer);
	}
}

template< typename T >
T* FastBuffer<T>::copy() {
	T* buf = new T[this->pos];
	memcpy(buf, this->buffer, this->pos * sizeof(T));

	return buf;
}

template< typename T >
T* FastBuffer<T>::data() {
	return this->buffer;
}

template< typename T >
int FastBuffer<T>::size() {
	return this->pos * sizeof(T);
}

template< typename T >
bool FastBuffer<T>::empty() {
	return this->pos == 0;
}

template< typename T >
int FastBuffer<T>::count() {
	return this->pos;
}

template< typename T >
int FastBuffer<T>::capacity() {
	return this->length;
}

template< typename T >
void FastBuffer<T>::clear() {
	this->pos = 0;
}

template< typename T >
void FastBuffer<T>::reserve( int count ) {
	while( this->pos + count > this->length ) {
		int new_size = this->length * 2;

#		if LT3D_VERBOSE_FAST_BUFFER == true
		logger::info("Buffer ", this, " resized to ", new_size, " (", new_size * sizeof(T), " bytes)");
#		endif

		this->buffer = (T*) realloc(this->buffer, new_size * sizeof(T));
		this->length = new_size;
	}
}

template< typename T >
T& FastBuffer<T>::read( int index ) {
	return this->buffer[index];
}

template< typename T >
void FastBuffer<T>::write( int index, T value ) {
	return this->buffer[index] = value;
}

template< typename T >
void FastBuffer<T>::remove( int index ) {
	std::copy(this->buffer + index + 1, this->buffer + this->pos, this->buffer + index);
	this->pos --;
}

template< typename T >
void FastBuffer<T>::insert( T data ) {
	this->reserve(1);
	this->push(data);
}

template< typename T >
void FastBuffer<T>::insert( T* array, int length ) {
	this->reserve(length);
	memcpy((this->buffer + this->pos), array, length * sizeof(T));

	this->pos += length;
}

