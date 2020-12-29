#pragma once

class Renderer {
private:
	static Renderer* m_instance;
	Renderer();

	SDL_Window* m_sdlWindow;
	SDL_Renderer* m_sdlRenderer;
	bool m_isMinimized;

public:
	~Renderer();
	static Renderer* GetInstance();

	bool Init();
	void Render();

	// This is used by the SDL event loop, should not be called elsewhere
	void UpdateIsMinimizedVar(bool isMinimized);
};