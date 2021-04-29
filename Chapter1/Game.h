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

	struct Vector2 {
		float x;
		float y;
	};

public:
	Vector2 mBallPos, mPaddlePos;
	const int width = 800;
	const int height = 600;
	const int paddleWidth = 10;
	const int paddleHeight = 50;
	const int thickness = 15; //used for wall and ball
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
};
#endif