#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>
#include <vector>

#include "Renderer.h"

Renderer* Renderer::m_instance = nullptr;

Renderer::Renderer() {
	m_sdlWindow = NULL;
	m_sdlRenderer = NULL;

	m_isMinimized = false;
}

Renderer::~Renderer() {
	SDL_DestroyWindow(m_sdlWindow);
	IMG_Quit();
}

Renderer* Renderer::GetInstance() {
	if(m_instance == nullptr) {
		m_instance = new Renderer();
	}
	return m_instance;
}

bool Renderer::Init() {
	// Init SDL_image
	if(!IMG_Init(IMG_INIT_PNG)) {
		printf("SDL_image initialization failed! Error: %s\n", IMG_GetError());
		return false;
	}
	printf("SDL_image initialized\n");

	// Create the SDL window
	m_sdlWindow = SDL_CreateWindow("ECS Prototype (Tyler McIntyre)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if(m_sdlWindow == NULL) {
		printf("Window creation failed! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	printf("SDL Window created\n");

	// Create the SDL renderer
	m_sdlRenderer = SDL_CreateRenderer(m_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	if(m_sdlRenderer == NULL) {
		printf("SDL Renderer creation failed! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	printf("SDL Renderer created\n");

	return true;
}

void Renderer::Render() {
	if(m_isMinimized) return;	// Don't render if minmized

	// Clear the screen
	SDL_SetRenderDrawColor(m_sdlRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_sdlRenderer);

	// TODO: Draw all entities with sprite + transform components
	SDL_SetRenderDrawColor(m_sdlRenderer, 255, 255, 255, 255);
	SDL_Rect r = { 50, 50, 50, 50 };
	SDL_RenderFillRect(m_sdlRenderer, &r);

	// Swap the buffers
	SDL_RenderPresent(m_sdlRenderer);
}

void Renderer::UpdateIsMinimizedVar(bool isMinimized) {
	m_isMinimized = isMinimized;
}