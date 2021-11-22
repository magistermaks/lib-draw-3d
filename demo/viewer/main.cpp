#include <core.hpp>

// minimal and simple example of .obj viewer

int main() {

	const int width = 1024;
	const int height = 768;

	// print current directory
	logger::info("Current working directory: ", std::filesystem::current_path().string());

	// open window
	if( !GLHelper::init(width, height, "Ring Demo") ) {
		return -1;
	}
	
	// window handle
	GLFWwindow* window = GLHelper::window();

	std::cout << "Enter relative or absolute path to file: ";
	std::string file;
	std::cin >> file;

	Mesh& object = Resource::object(file, LD3D_OBJ_VT).get();

	Context context;

	// compile simple shader program
	ShaderProgram* shader = context.loadShader("surface");

	// get uniforms
	auto loc_matrix = shader->location("model_view_projection_mat");;
	auto loc_texture = shader->location("sampler");
	
	// create the projection matrix (perspective)
	glm::mat4 projection = glm::perspective(glm::radians(77.5f), (float) width / (float) height, 0.1f, 1000.0f);

	// buffer builder
	VertexConsumerProvider provider3d;
	provider3d.attribute(3); // 0 -> pos [x, y, z]
	provider3d.attribute(2); // 1 -> tex [u, v]

	// geometry buffer
	VertexConsumer consumer3d = provider3d.get();

	// send model to gpu
	consumer3d.clear();
	consumer3d.vertex(object.buffer.data(), object.buffer.count());
	consumer3d.shrink();
	consumer3d.submit();

	// create render pipeline
	Pipeline pipeline = Pipeline()
		.setShader(shader)
		.setConsumer(&consumer3d)
		.setTexture(object.material.diffuse_map, 0);

	// create camera, and move it to pos (20, 20, 20)
	Camera camera;
	camera.move( glm::vec3(20, 20, 20) );
	
	glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(10, 10, 10));
	glm::mat4 view;

	do {

		// clear the screan, direct OpenGL call
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// update camera with keyboard input
		camera.update();

		// enable rendering pipeline
		pipeline.bind();
		{
		
			// update view matrix
			view = camera.getView();	

			// send matrix to shader
			loc_matrix.set(projection * view * model);

			// send texture unit to shader
			loc_texture.set(0);

		}
		pipeline.draw();

		// update screan
		GLHelper::frame();

	// exit if ESC is pressed (or the X key)
	} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

	delete shader;
	return 0;
}

