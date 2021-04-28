#ifndef GAME_H
#define GAME_H

#include <SDL.h>

class Game {
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	SDL_Window* mWindow;
	bool mIsRunning;
	SDL_Renderer* mRenderer;

public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
};
#endif