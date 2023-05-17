#include <Engine/resources/loader.h>
#include <Engine/Engine.h>
#include <Engine/Tests.h>

int	main(int argc, char **argv)
{

	Engine::Tests::run_tests();

	SDL_Window *window = Engine::initialize_window();
	bool running = true;
	Engine::handle_engine_loop(window, running);

	return 0;
}