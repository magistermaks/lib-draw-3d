#include "storage.hpp"

//StorageBuffer::StorageBuffer( int binding ) {
//	glGenBuffers(1, &ssbo);
//	this->binding = binding;
//}
//
//StorageBuffer::StorageBuffer( StorageBuffer&& buffer ) : ssbo(buffer.ssbo), binding(buffer.binding), buffer(std::move(buffer.buffer)) {
//	buffer.ssbo = 0;
//}
//
//StorageBuffer::~StorageBuffer() {
//	glDeleteBuffers(1, &ssbo);
//}
//
//void StorageBuffer::bind() {
//	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
//	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, this->binding, this->ssbo);
//}
//
//void StorageBuffer::submit() {
//	this->bind();
//
//	glBufferData(GL_SHADER_STORAGE_BUFFER, this->buffer.size() * sizeof(T), this->buffer.data(), GL_DYNAMIC_DRAW);
//}
//
