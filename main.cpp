#include <iostream>
#include "SDL.h"
#include "function.h"

#define WINDOW_TITLE "Graph"
#define WINDOW_WIDTH 640.0
#define WINDOW_HEIGHT 480.0

#define LINES 8.0

#define X_UNIT 2.0
#define Y_UNIT 2.0
#define STEP 0.1

int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not be initialized: " << SDL_GetError() << std::endl;
	}

	window = SDL_CreateWindow(
			WINDOW_TITLE,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			SDL_WINDOW_OPENGL
	);

	if (window == nullptr) {
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cout << "Could not create SDL renderer: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);

	for (int i = 1; i < LINES; i++) {
		SDL_RenderDrawLine(renderer, 0, i * WINDOW_HEIGHT / LINES, WINDOW_WIDTH, i * WINDOW_HEIGHT / LINES);
		SDL_RenderDrawLine(renderer, i * WINDOW_WIDTH / LINES, 0, i * WINDOW_WIDTH / LINES, WINDOW_HEIGHT);
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	try {
		std::unique_ptr<Function> function = Function::parse("+3");

		double i = X_UNIT * -LINES / 2;

		int x_prev_coordinate = 0;
		int y_prev_coordinate = -function->f(i) / Y_UNIT / LINES * WINDOW_HEIGHT + WINDOW_HEIGHT / 2;

		for (i += STEP / X_UNIT; i <= X_UNIT * LINES / 2 + STEP / X_UNIT; i += STEP / X_UNIT) {
			double y = function->f(i);

			int x_coordinate = i / X_UNIT / LINES * WINDOW_WIDTH + WINDOW_WIDTH / 2;
			int y_coordinate = -y / Y_UNIT / LINES * WINDOW_HEIGHT + WINDOW_HEIGHT / 2;

			SDL_RenderDrawLine(renderer, x_prev_coordinate, y_prev_coordinate, x_coordinate, y_coordinate);

			x_prev_coordinate = x_coordinate;
			y_prev_coordinate = y_coordinate;
		}
	} catch (std::exception &e) {
		std::cerr << "Could not parse the function string" << std::endl;
	}

	SDL_RenderPresent(renderer);

	SDL_Event event;
	bool quit = false;

	while (!quit && SDL_WaitEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();
	return EXIT_SUCCESS;
}
