#pragma once

#include "light.hpp"
#include "buffer/storage.hpp"
#include <include/external.hpp>

class Context {

	private:

		StorageBuffer<Light> lights;
		GLuint lights_buffer_base = 0;

	public:

		Context() : lights(0) {
			
			

		}

		Light& addLight( LightType type ) {
			lights.push(Light(type));
			return lights.get(lights.count() - 1);
		}

		Light& getLight( int index ) {
			return lights.get(index);
		}

		Light& peekLight( int index ) {
			return lights.peek(index);
		}

		void removeLight( int index ) {
			lights.remove(index);
		}

		int lightCount() {
			return lights.count();
		}

		void submit() {
			lights.submit();
		}

};

