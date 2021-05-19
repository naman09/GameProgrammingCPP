#ifndef GAME_H
#define GAME_H

#include <SDL.h>

class Game {
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool mIsRunning;
	Uint32 mTickCount;
public:
	Game();
	void Initialize();
	void RunLoop();
	void Shutdown();
};

#endif
