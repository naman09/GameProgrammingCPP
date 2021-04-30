#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>

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

	struct Ball {
		Vector2 mBallPos;
		Vector2 mBallVel;
	};

public:
	std::vector<Ball> balls;
	//Vector2 mBallPos;
	Vector2 mPaddleLeftPos;
	int mPaddleLeftDir;
	Vector2 mPaddleRightPos;
	int mPaddleRightDir;
	Vector2 mBallVel;
	const int width{ 800 };
	const int height{ 600 };
	const int paddleWidth{ 10 };
	const int paddleHeight{ 100 };
	const int thickness{ 15 }; //used for wall and ball
	Uint32 mTicksCount;
	
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
};
#endif