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
	ShaderProgram* light = GLHelper::loadShaderProgram("phong");
	ShaderProgram* source = GLHelper::loadShaderProgram("source");

	GLint loc_projection = light->location("projection");
	GLint loc_view = light->location("view");
	GLint loc_model = light->location("model");
	GLint loc_objectColor = light->location("objectColor");
	GLint loc_lightColor = light->location("lightColor");
	GLint loc_lightPos = light->location("lightPos");
	GLint loc_cameraPos = light->location("viewPos");

	GLint loc_mvp = source->location("mvp");

	glm::mat4 proj = glm::perspective(glm::radians(77.5f), (float) width / (float) height, 0.1f, 1000.0f);

	Charset charset( "assets/8x8font.png" );

	time_t last = 0;
	long count = 0, fps = 0, ms = 0;

	auto& renderer = RenderSystem::instance();

	Texture* box = Texture::fromFile("./assets/box.png");

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

		glm::vec3 light_source(x, y, z);
		glm::vec3 light_color(1, 1, 1);

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
		renderer.setTexture(*box);

		glm::mat4 model = MatrixHelper::getModelIdentity();
		model = glm::scale(model, glm::vec3(10, 10, 10));
//		model = glm::translate(model, glm::vec3(1, 1, 0));
		glm::mat4 view = camera.getView();

//		glm::mat4 mvp = proj * camera.getView() * model;
		MatrixHelper::uniform(loc_projection, proj);
		MatrixHelper::uniform(loc_model, model);
		MatrixHelper::uniform(loc_view, view);

		glm::vec3 cameraPos = camera.getPosition();

		glUniform3fv(loc_lightColor, 1, glm::value_ptr(light_color));
		glUniform3fv(loc_lightPos, 1, glm::value_ptr(light_source));
		glUniform3fv(loc_cameraPos, 1, glm::value_ptr(cameraPos));

		renderer.draw();

		source->bind();
		renderer.setShader(*source);

		model = glm::mat4(1.0f);
		model = glm::translate(model, light_source);

		glm::mat4 mvp = proj * view * model;
		MatrixHelper::uniform(loc_mvp, mvp);

		renderer.draw();

		GLHelper::frame();
		count ++;

		ms = (ms + std::chrono::duration_cast<milliseconds>( Clock::now() - start ).count())/2;

	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

	delete layer, light, source;

	return 0;
}

