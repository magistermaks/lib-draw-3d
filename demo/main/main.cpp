#include <core.hpp>

int main() {

	const int width = 1024;
	const int height = 768;

	// print cwd, nice for debugging
	logger::info("Current working directory: '", std::filesystem::current_path().string(), "'");

	// initilize GLFW, GLEW, OpenGL, and OpenCL
	if( !GLHelper::init(width, height, "Ring Demo") ) {
		return -1;
	}
	
	GLFWwindow* window = GLHelper::window();

	// compile shader program
	ShaderProgram* layer = GLHelper::loadShaderProgram("layer");
	ShaderProgram* source = GLHelper::loadShaderProgram("source");

	Context context;

	ShaderProgram* light = context.loadShader("phong");

	auto loc_view_projection = light->location("view_projection_mat");
	auto loc_model = light->location("model_mat");
	auto loc_normal = light->location("normal_mat");
	auto loc_camera_position = light->location("camera");

	auto loc_texture = light->location("sampler");
	auto loc_specular = light->location("material.specular");
	auto loc_emissive = light->location("material.emissive");
	auto loc_shininess = light->location("material.shininess");

	auto loc_mvp = source->location("mvp");
	auto loc_col = source->location("col");

	glm::mat4 proj = glm::perspective(glm::radians(77.5f), (float) width / (float) height, 0.1f, 1000.0f);

	Charset charset( "assets/8x8font.png" );

	time_t last = 0;
	long count = 0, fps = 0, ms = 0;

	auto& renderer = RenderSystem::instance();

	Texture* box_texture = Texture::fromFile("./assets/box-texture.png");
	Texture* box_specular = Texture::fromFile("./assets/box-specular.png");
	Texture* box_emissive = Texture::fromFile("./assets/box-emissive.png");

	VertexConsumerProvider provider2d;
	provider2d.attribute(2); // 0 -> pos [x, y]
	provider2d.attribute(2); // 1 -> tex [u, v]

	VertexConsumer consumer2d = provider2d.get();

	VertexConsumerProvider provider3d;
	provider3d.attribute(3); // 0 -> pos [x, y, z]
	provider3d.attribute(3); // 1 -> nor [x, y, z] 
	provider3d.attribute(2); // 2 -> tex [u, v]

	VertexConsumer consumer3d = provider3d.get();

	VertexConsumerProvider provider3di;
	provider3di.attribute(3); // 0 -> pos [x, y, z]
	provider3di.attribute(3); // 1 -> nor [x, y, z] 
	provider3di.attribute(2); // 2 -> tex [u, v]
	provider3di.target(Consumer::INSTANCE);
	provider3di.attribute(3); // 3 -> col [r, g, b]
	provider3di.attribute(4); // 4 -> mvp [a1, b2, c3, d4]
	provider3di.attribute(4); // 5 -> mvp [a1, b2, c3, d4]
	provider3di.attribute(4); // 6 -> mvp [a1, b2, c3, d4]
	provider3di.attribute(4); // 7 -> mvp [a1, b2, c3, d4]

	VertexConsumer consumer3di = provider3di.get();

	consumer3d.vertex( -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f );
	consumer3d.vertex(  0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f );
	consumer3d.vertex(  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f );
	consumer3d.vertex(  0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f );
	consumer3d.vertex( -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f );
	consumer3d.vertex( -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f );

	consumer3d.vertex( -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f );
	consumer3d.vertex(  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f );
	consumer3d.vertex(  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f );
	consumer3d.vertex(  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f );
	consumer3d.vertex( -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f );
	consumer3d.vertex( -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f );

	consumer3d.vertex( -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f );
	consumer3d.vertex( -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f );
	consumer3d.vertex( -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f );
	consumer3d.vertex( -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f );
	consumer3d.vertex( -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f );
	consumer3d.vertex( -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f );

	consumer3d.vertex(  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f );
	consumer3d.vertex(  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f );
	consumer3d.vertex(  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f );
	consumer3d.vertex(  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f );
	consumer3d.vertex(  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f );
	consumer3d.vertex(  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f );

	consumer3d.vertex( -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f );
	consumer3d.vertex(  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f );
	consumer3d.vertex(  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f );
	consumer3d.vertex(  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f );
	consumer3d.vertex( -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f );
	consumer3d.vertex( -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f );

	consumer3d.vertex( -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f );
	consumer3d.vertex(  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f );
	consumer3d.vertex(  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f );
	consumer3d.vertex(  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f );
	consumer3d.vertex( -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f );
	consumer3d.vertex( -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f );

	consumer3d.shrink();
	consumer3d.submit();

	consumer3di.vertex(consumer3d);

	context.addLight(LightType::Point)
		.setColor(1, 1, 1)
		.setAttenuation(0.014, 0.0007);

	context.addLight(LightType::Point)
		.setColor(1, 0.65, 0.55)
		.setAttenuation(0.014, 0.0007);

	// shaded cube pipeline
	Pipeline pipeline = Pipeline()
		.setShader(light)
		.setConsumer(&consumer3d)
		.setTexture(box_texture, 0)
		.setTexture(box_specular, 1)
		.setTexture(box_emissive, 2);

	Pipeline sources = Pipeline()
		.setShader(source)
		.setConsumer(&consumer3di);

	Camera camera;
	camera.move( glm::vec3(20, 20, 20) );

	float x, y, z;
	float radius = 15.0f;
	float angle = 3;
	static bool f = true;

	glfwSetKeyCallback( GLHelper::window(), [] (GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
		if( key == GLFW_KEY_X && action == GLFW_PRESS ) f = !f;
		if( key == GLFW_KEY_SPACE && action == GLFW_PRESS ) GLHelper::screenshot("screenshot.png");
	} );

	do {

		x = radius * cos(angle);
		y = sin(angle) * radius / 2;
		z = radius * sin(angle);

		if(f) angle += 0.0001f;

		glm::vec3 light_source(x, y, z), light2_source(-x, 5, -z);
		glm::vec3 light_color(1, 1, 1), light2_color(1, 0.65, 0.55);

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		auto start = Clock::now();

		Threads::execute();

		// update the fps count
		if( last != time(0) ) {
			last = time(0);
			fps = count;
			count = 0;
		}

		camera.update();
	
		renderer.setConsumer(consumer2d);
		renderer.setShader(*layer);
		renderer.drawText( "FPS: " + std::to_string(fps) + " (avg: " + std::to_string(ms) + "ms)", -1, 1-0.05, 0.04, charset ); 

		pipeline.bind();
		//{

			glm::mat4 model(1.0f);
			model = glm::scale(model, glm::vec3(10, 10, 10));
			glm::mat4 view = camera.getView(), view_proj = proj * view;
			glm::mat3 normal = glm::mat3( glm::transpose( glm::inverse( model ) ) );
	
			loc_view_projection.set(view_proj);
			loc_model.set(model);
			loc_normal.set(normal);

			glm::vec3 camera_position = camera.getPosition();

			context.getLight(0).setPosition(light_source);
			context.getLight(1).setPosition(light2_source);

			context.submit();

			loc_camera_position.set(camera_position);

			// textures
			loc_texture.set(0); // unit 0
			loc_specular.set(1); // unit 1
			loc_emissive.set(2); // unit 2

			loc_shininess.set(16.0f);

		//}
		pipeline.draw();

		consumer3di.clearInstance();

		{
			consumer3di.instance(light_color.r, light_color.g, light_color.b);
			glm::mat4 mvp = proj * view * glm::translate(glm::mat4(1), light_source);
			float* arr = (float*) &mvp[0];

			consumer3di.instance(*(arr+0 ), *(arr+1 ), *(arr+2 ), *(arr+3 ));
			consumer3di.instance(*(arr+4 ), *(arr+5 ), *(arr+6 ), *(arr+7 ));
			consumer3di.instance(*(arr+8 ), *(arr+9 ), *(arr+10), *(arr+11));
			consumer3di.instance(*(arr+12), *(arr+13), *(arr+14), *(arr+15));
		}

		{
			consumer3di.instance(light2_color.r, light2_color.g, light2_color.b);
			glm::mat4 mvp = proj * view * glm::translate(glm::mat4(1), light2_source);
			float* arr = (float*) &mvp[0];

			consumer3di.instance(*(arr+0 ), *(arr+1 ), *(arr+2 ), *(arr+3 ));
			consumer3di.instance(*(arr+4 ), *(arr+5 ), *(arr+6 ), *(arr+7 ));
			consumer3di.instance(*(arr+8 ), *(arr+9 ), *(arr+10), *(arr+11));
			consumer3di.instance(*(arr+12), *(arr+13), *(arr+14), *(arr+15));
		}

		consumer3di.submit();

		sources.bind();
		
		// custom draw calls, piplies doesn't support instancing yet
		{
			for(int unit = 0; unit < sources.textures.size(); unit ++) {
				sources.textures[unit]->bind(unit);
			}	

			sources.consumer->bind();

			glDrawArraysInstanced(GL_TRIANGLES, 0, consumer3di.count(), 2);
		}
//
		GLHelper::frame();
		count ++;

		ms = (ms + std::chrono::duration_cast<milliseconds>( Clock::now() - start ).count())/2;

	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

	delete layer, light, source;

	return 0;
}

