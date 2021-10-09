#include <core.hpp>

struct SSBOLight {

	// type == color.w

	glm::vec4 color;
	glm::vec4 position;
	glm::vec4 direction;
	
	// spotlight cutoff angle
	float angle_inner;
	float angle_outer;

	// attenuation
	float linear;
	float quadratic;
};

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
	ShaderProgram* light = GLHelper::loadShaderProgram("phong"); //gouraud
	ShaderProgram* source = GLHelper::loadShaderProgram("source");

	auto loc_view_projection = light->location("view_projection_mat");
	auto loc_model = light->location("model_mat");
	auto loc_normal = light->location("normal_mat");
	auto loc_1light_color = light->location("lights[0].color");
	auto loc_1light_source = light->location("lights[0].position");
	auto loc_1light_type = light->location("lights[0].type");
	auto loc_2light_color = light->location("lights[1].color");
	auto loc_2light_source = light->location("lights[1].position");
	auto loc_2light_type = light->location("lights[1].type");
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
	provider3d.attribute(2); // 1 -> tex [u, v]

	VertexConsumer consumer3d = provider3d.get();

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

	consumer3d.submit();

	StorageBuffer<SSBOLight> storage(0);

	storage.push( (SSBOLight) {
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), // color
		glm::vec4(6.0f, 6.0f, 6.0f, 0.0f), // position
		glm::vec4(1.0f), // direction (unused)
		2, 3, // angle (unused)
		0.022, 0.0019 // attenuation
	} );

	storage.push( (SSBOLight) {
		glm::vec4(1, 0.65, 0.55, 1.0f), // color
		glm::vec4(-6.0f, -6.0f, -6.0f, 0.0f), // position
		glm::vec4(1.0f), // direction (unused)
		2, 3, // angle (unused)
		0.022, 0.0019 // attenuation
	} );

	storage.submit();

	Camera camera;

	// move the camera so that we don't start inside a black cube
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

		glm::vec4 light_source(x, y, z, 1), light2_source(-x, 5, -z, 1);
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
		renderer.depthTest(false);
		renderer.depthMask(false);
		renderer.setShader(*layer);
		renderer.drawText( "FPS: " + std::to_string(fps) + " (avg: " + std::to_string(ms) + "ms)", -1, 1-0.05, 0.04, charset ); 

		renderer.depthMask(true);
		renderer.depthTest(true);

		light->bind(); // uniform
		renderer.setShader(*light);
		renderer.setConsumer(consumer3d);
		renderer.setTexture(*box_texture, 0);
		renderer.setTexture(*box_specular, 1);
		renderer.setTexture(*box_emissive, 2);

		glm::mat4 model = MatrixHelper::getModelIdentity();
		model = glm::scale(model, glm::vec3(10, 10, 10));
//		model = glm::translate(model, glm::vec3(1, 1, 0));
		glm::mat4 view = camera.getView(), view_proj = proj * view;
		glm::mat3 normal = glm::mat3( glm::transpose( glm::inverse( model ) ) );

		loc_view_projection.set(view_proj);
		loc_model.set(model);
		loc_normal.set(normal);

		glm::vec3 camera_position = camera.getPosition();

		storage.get(0).position = light_source;
		storage.get(1).position = light2_source;

		storage.submit();

		loc_camera_position.set(camera_position);

		// textures
		loc_texture.set(0); // unit 0
		loc_specular.set(1); // unit 1
		loc_emissive.set(2); // unit 2

		loc_shininess.set(16.0f);

		storage.bind();

		renderer.draw();

		source->bind();
		renderer.setShader(*source);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(light_source));

		glm::mat4 mvp = proj * view * model;
		loc_mvp.set(mvp);
		loc_col.set(light_color);

		renderer.draw();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(light2_source));

		mvp = proj * view * model;
		loc_mvp.set(mvp);
		loc_col.set(light2_color);

		renderer.draw();

		GLHelper::frame();
		count ++;

		ms = (ms + std::chrono::duration_cast<milliseconds>( Clock::now() - start ).count())/2;

	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

	delete layer, light, source;

	return 0;
}

