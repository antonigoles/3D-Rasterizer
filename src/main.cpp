#include "Engine/Engine.h"

void test() 
{
	std::string path = "C:/Users/Antoni/Desktop/3d-rasterizer/assets/Meshes/cube.3d";
	Engine::Mesh *mesh = Engine::load_mesh_from_native_engine_file(path);
	mesh->print_mesh();
}

int	main(int argc, char **argv)
{
	
	test();

	SDL_Window *window = Engine::initialize_window();
	bool running = true;
	Engine::handle_engine_loop(window, running);

	return 0;
}