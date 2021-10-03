#pragma once

#include <include/external.hpp>

//enum struct LightType : int {
//	Null   = 0,
//	Point  = 1,
//	Spot   = 2,
//	Global = 3
//}
//
//class Light {
//
//	private:
//
//		const LightType type;
//
//		glm::vec3 diffuse_color, specular_color;
//		glm::vec3 position, direction;
//	
//		// spot light
//		float angle_inner;
//		float angle_outer;
//
//		// attenuation
//		float linear;
//		float quadratic;
//
//	public:
//
//		Light(LightType type);
//
//		Light& setColor( const glm::vec3& color );
//		Light& setDiffuseColor( const glm::vec3& color );
//		Light& setSpecularColor( const glm::vec3& color );
//		Light& setAttenuation( float linear, float quadratic );
//		Light& setAngle( float inner, float outer );
//		Light& setPosition( const glm::vec3& position );
//		Light& setDirection( const glm::vec3& direction );
//
//}
