#include <cmath>
#include "Game.h"

Game::Game() {
	mWindow = nullptr;
	mIsRunning = true;
	mRenderer = nullptr;
	mBallPos.x = 50.0f;
	mBallPos.y = 70.0f;
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 300.0f;
	mTicksCount = 0;
	mBallVel.x = 200.0f;
	mBallVel.y = 235.0f;
}

void Game::ProcessInput() {
	SDL_Event event;
	//SDL event queue contain events recieved from OS 
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
		mPaddleDir += 1;
	}
}

void Game::UpdateGame() {
	//wait until 16ms is elapsed (1frame in 1000ms/60)
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();
	if (deltaTime > 0.05f) { //clamp the delta time
		deltaTime = 0.05f;
	}

	//update paddle
	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime; //300 is velocity

		//prevent the paddle to go out of bounds
		float lowerBound = thickness + (paddleHeight / 2.0f);
		float upperBound = height - (paddleHeight / 2.0f) - thickness;
		if (mPaddlePos.y < lowerBound) {
			mPaddlePos.y = lowerBound;
		}
		if (mPaddlePos.y > upperBound) {
			mPaddlePos.y = upperBound;
		}
	}

	//update ball
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	if (mBallPos.y <= 3 * thickness / 2.0f && mBallVel.y < 0.0f) {
		mBallVel.y = -mBallVel.y;
	}
	
	if (mBallPos.y >= (height - 3 * thickness / 2.0f) && mBallVel.y > 0.0f) {
		mBallVel.y = -mBallVel.y;
	}
	if (mBallPos.x >= (width - thickness) && mBallVel.x > 0.0f) {
		mBallVel.x = -mBallVel.x;
	}
	if ((fabsf(mBallPos.x - mPaddlePos.x) <= (thickness + paddleWidth) / 2.0f) &&
		(fabsf(mBallPos.y - mPaddlePos.y) <= (thickness + paddleHeight) / 2.0f) && 
		mBallVel.x < 0.0f) {
		mBallVel.x = -mBallVel.x;
	}
	if (mBallPos.x < 0) {
		mIsRunning = false;
	}
}

void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255); //Set the drawing color
	SDL_RenderClear(mRenderer); // clear the back buffer and paint with drawing color
	
	//Actual game scene drawing 
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	SDL_Rect topWall{ 0, 0, width, thickness };
	SDL_RenderFillRect(mRenderer, &topWall);

	SDL_Rect rightWall{ width-thickness, 0, thickness, height };
	SDL_RenderFillRect(mRenderer, &rightWall);

	SDL_Rect bottomWall{ 0, height-thickness, width, thickness };
	SDL_RenderFillRect(mRenderer, &bottomWall);

	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x - paddleWidth / 2),
		static_cast<int>(mPaddlePos.y - paddleHeight / 2),
		paddleWidth,
		paddleHeight
	};
	SDL_RenderFillRect(mRenderer, &paddle);
	SDL_RenderPresent(mRenderer); //swap the front and back buffer
}

bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	
	if (sdlResult != 0) { //sdl fails
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("Game Programming in c++ (chapter 1)", // window title
		100, // Top left x-coord of window
		100, // Top left y-coord of window
		width, // width
		height, // height
		0 // Flags (0 for no flag set)
	);

	if (!mWindow) { //window fails
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow,
		-1,
		SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC //enable v-sync
	);

	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	return true; // success 
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

