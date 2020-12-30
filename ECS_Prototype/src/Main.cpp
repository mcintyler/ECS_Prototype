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
	Entity* ent = ecs->CreateEntity();
	Components::Transform transComp = Components::Transform();
	transComp.x = 20;
	transComp.y = 300;
	ent->AddComponent(ComponentID::Transform, &transComp);
	Components::DrawRect drawComp = Components::DrawRect();
	drawComp.w = 50;
	drawComp.h = 50;
	drawComp.r = 204;
	drawComp.g = 78;
	drawComp.b = 189;
	ent->AddComponent(ComponentID::DrawRect, &drawComp);
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
			ent->ClearComponents();
			Components::Transform* transform = (Components::Transform*)ent->GetComponent(ComponentID::Transform);
			if(transform != nullptr) {
				transform->x = 100;
			}
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
		printf("[Renderer] Initialization failed!\n");
		return false;
	}
	printf("[Renderer] Initialized\n");

	// Init ECS
	ECS* ecs = ECS::GetInstance();
	if(!ecs->Init(3, sizeof(Components::Transform),
					sizeof(Components::Velocity),
					sizeof(Components::DrawRect))) {
		printf("[ECS] Initialization failed!\n");
		return false;
	}
	printf("[ECS] ECS initialized\n");

	return true;
}

void Close() {
	ECS::GetInstance()->FreeComponentStore();
	SDL_Quit();
}