#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Actor.h"
#include <vector>

class Game {
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool mIsRunning;
	SDL_Renderer* mRenderer;
	Uint32 mTickCount;
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
public:
	Game();
	void Initialize();
	void RunLoop();
	void Shutdown();
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
};

#endif
