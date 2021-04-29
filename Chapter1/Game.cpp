#include "Game.h"

Game::Game() {
	mWindow = nullptr;
	mIsRunning = true;
	mRenderer = nullptr;
	mBallPos.x = 50;
	mBallPos.y = 70;
	mPaddlePos.x = 10;
	mPaddlePos.y = 300;
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
}

void Game::UpdateGame() {
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

