//#include "light.hpp"
//
//Light::Light(LightType type) : type(type) {
//
//}
//
//Light& Light::setColor( const glm::vec3& color ) {
//	this->diffuse_color = color;
//	this->specular_color = color;
//	this->modified = true;
//}
//
//Light& Light::setDiffuseColor( const glm::vec3& color ) {
//	this->diffuse_color = color;
//	this->modified = true;
//}
//
//Light& Light::setSpecularColor( const glm::vec3& color ) {
//	this->specular_color = color;
//	this->modified = true;
//}
//
//Light& Light::setAttenuation( float linear, float quadratic ) {
//	this->linear = linear;
//	this->quadratic = quadratic;
//	this->modified = true;
//}
//
//Light& Light::setAngle( float inner, float outer ) {
//	this->angle_inner = inner;
//	this->angle_outer = outer;
//	this->modified = true;
//}
//
//Light& Light::setPosition( const glm::vec3& position ) {
//	this->position = position;
//	this->modified = true;
//}
//
//Light& Light::setDirection( const glm::vec3& direction ) {
//	this->direction = direction;
//	this->modified = true;
//}
//
//bool Light::getModified() {
//	return this->modified;
//}
//
//void Light::upload(GLint location, GLint index) {
//	glUniform1i  (0 + location, this->type);
//	glUniform3fv (1 + location, this->diffuse_color);
//	glUniform3fv (
//}
//
