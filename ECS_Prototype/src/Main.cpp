#include <SDL.h>
#include <stdio.h>
#include <string>
#include "Renderer.h"
#include "ECS/ECS.h"

bool Init();
void Close();

int main(int argc, char* args[]) {
	if(!Init()) {
		printf("CRITICAL ERROR: Init failed!\n");
		return 1;
	}

	bool shouldQuit = false;
	SDL_Event e;
	Uint64 nowTime = SDL_GetPerformanceCounter();
	Uint64 lastTime = 0;
	double deltaTime = 0.0f;

	// Cache singletons
	Renderer* renderer = Renderer::GetInstance();
	ECS* ecs = ECS::GetInstance();

	// !! REMOVE LATER !!
	ecs->CreateEntity();
	double counter = 0.0f;
	bool count = true;

	while(!shouldQuit) {
		// Calculate delta time
		lastTime = nowTime;
		nowTime = SDL_GetPerformanceCounter();
		deltaTime = ((nowTime - lastTime) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001;

		// Handle events
		while(SDL_PollEvent(&e) != 0) {
			switch(e.type) {
				case SDL_QUIT:
					shouldQuit = true;
					break;
				case SDL_WINDOWEVENT:
					switch(e.window.event) {
						case SDL_WINDOWEVENT_MINIMIZED:
							renderer->UpdateIsMinimizedVar(true);
							break;
						case SDL_WINDOWEVENT_RESTORED:
							renderer->UpdateIsMinimizedVar(false);
							break;
					}
			}
		}

		// !! REMOVE LATER !!
		counter += deltaTime;
		if(count && counter >= 3.0f) {
			ecs->KillEntity(0);
			count = false;
		}

		// Render
		renderer->Render();
	}

	// Clean up and quit
	Close();
}

bool Init() {
	// Init SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	printf("SDL subsystems initialized\n");

	// Init Renderer
	Renderer* renderer = Renderer::GetInstance();
	if(!renderer->Init()) {
		printf("Renderer initialization failed! (Not the SDL_Renderer)\n");
		return false;
	}
	printf("Renderer initialized\n");

	return true;
}

void Close() {
	SDL_Quit();
}