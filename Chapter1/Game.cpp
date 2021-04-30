#include <cmath>
#include <cstdlib>
#include "Game.h"

Game::Game() {
	mWindow = nullptr;
	mIsRunning = true;
	mRenderer = nullptr;
	mTicksCount = 0;
	mPaddleLeftPos.x = 10.0f;
	mPaddleLeftPos.y = 300.0f;
	mPaddleRightPos.x = width - 10.0f;
	mPaddleRightPos.y = 300.0f;
	mPaddleLeftDir = 0;
	mPaddleRightDir = 0;
	/*mBallPos.x = 50.0f;
	mBallPos.y = 70.0f;
	mBallVel.x = 200.0f;
	mBallVel.y = 235.0f;*/
	int rangeLeft = width / 4;
	int rangeRight = width / 2;
	for (int i = 0; i < 3; i++) {
		Ball ball;
		ball.mBallPos.x = static_cast<float>(rangeLeft + rand()%(rangeRight-rangeLeft));
		ball.mBallPos.y = static_cast<float>(rand()%height);
		ball.mBallVel.x = 100.0f;
		ball.mBallVel.y = 135.0f;
		balls.push_back(ball);
	}
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
	mPaddleLeftDir = 0;
	if (state[SDL_SCANCODE_W]) {
		mPaddleLeftDir -= 1;
	}
	if (state[SDL_SCANCODE_S]) {
		mPaddleLeftDir += 1;
	}
	mPaddleRightDir = 0;
	if (state[SDL_SCANCODE_I]) {
		mPaddleRightDir -= 1;
	}
	if (state[SDL_SCANCODE_K]) {
		mPaddleRightDir += 1;
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

	//update left paddle
	if (mPaddleLeftDir != 0) {
		mPaddleLeftPos.y += mPaddleLeftDir * 500.0f * deltaTime; //300 is velocity

		//prevent the paddle to go out of bounds
		float lowerBound = thickness + (paddleHeight / 2.0f);
		float upperBound = height - (paddleHeight / 2.0f) - thickness;
		if (mPaddleLeftPos.y < lowerBound) {
			mPaddleLeftPos.y = lowerBound;
		}
		if (mPaddleLeftPos.y > upperBound) {
			mPaddleLeftPos.y = upperBound;
		}
	}

	//update right paddle
	if (mPaddleRightDir != 0) {
		mPaddleRightPos.y += mPaddleRightDir * 500.0f * deltaTime; //300 is velocity

		//prevent the paddle to go out of bounds
		float lowerBound = thickness + (paddleHeight / 2.0f);
		float upperBound = height - (paddleHeight / 2.0f) - thickness;
		if (mPaddleRightPos.y < lowerBound) {
			mPaddleRightPos.y = lowerBound;
		}
		if (mPaddleRightPos.y > upperBound) {
			mPaddleRightPos.y = upperBound;
		}
	}


	//update ball

	for (Ball& ball : balls) {
		ball.mBallPos.x += ball.mBallVel.x * deltaTime;
		ball.mBallPos.y += ball.mBallVel.y * deltaTime;

		if (ball.mBallPos.y <= 3 * thickness / 2.0f && ball.mBallVel.y < 0.0f) { //top wall
			ball.mBallVel.y = -ball.mBallVel.y;
		}
		if (ball.mBallPos.y >= (height - 3 * thickness / 2.0f) && ball.mBallVel.y > 0.0f) { //bottom wall
			ball.mBallVel.y = -ball.mBallVel.y;
		}
		//if (mBallPos.x >= (width - thickness) && mBallVel.x > 0.0f) { //right wall
		//	mBallVel.x = -mBallVel.x;
		//}
		if ((fabsf(ball.mBallPos.x - mPaddleLeftPos.x) <= (thickness + paddleWidth) / 2.0f) &&
			(fabsf(ball.mBallPos.y - mPaddleLeftPos.y) <= (thickness + paddleHeight) / 2.0f) &&
			ball.mBallVel.x < 0.0f) { //ball left paddle collision
			ball.mBallVel.x = -ball.mBallVel.x;
		}
		if ((fabsf(ball.mBallPos.x - mPaddleRightPos.x) <= (thickness + paddleWidth) / 2.0f) &&
			(fabsf(ball.mBallPos.y - mPaddleRightPos.y) <= (thickness + paddleHeight) / 2.0f) &&
			ball.mBallVel.x > 0.0f) { //ball right paddle collision
			ball.mBallVel.x = -ball.mBallVel.x;
		}
		if (ball.mBallPos.x < 0 || ball.mBallPos.x > width) {
			mIsRunning = false;
		}
	}

	
}

void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255); //Set the drawing color
	SDL_RenderClear(mRenderer); // clear the back buffer and paint with drawing color
	
	//Actual game scene drawing 
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	
	SDL_Rect topWall{ 0, 0, width, thickness };
	SDL_RenderFillRect(mRenderer, &topWall);

	/*SDL_Rect rightWall{ width-thickness, 0, thickness, height };
	SDL_RenderFillRect(mRenderer, &rightWall);*/

	SDL_Rect bottomWall{ 0, height-thickness, width, thickness };
	SDL_RenderFillRect(mRenderer, &bottomWall);

	/*SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);*/

	//draw all balls
	for (Ball& ball : balls) {
		SDL_Rect drawBall{
		static_cast<int>(ball.mBallPos.x - thickness / 2),
		static_cast<int>(ball.mBallPos.y - thickness / 2),
		thickness,
		thickness
		};
		SDL_RenderFillRect(mRenderer, &drawBall);
	}
	
	SDL_Rect paddleLeft{
		static_cast<int>(mPaddleLeftPos.x - paddleWidth / 2),
		static_cast<int>(mPaddleLeftPos.y - paddleHeight / 2),
		paddleWidth,
		paddleHeight
	};
	SDL_RenderFillRect(mRenderer, &paddleLeft);
	SDL_Rect paddleRight{
		static_cast<int>(mPaddleRightPos.x - paddleWidth / 2),
		static_cast<int>(mPaddleRightPos.y - paddleHeight / 2),
		paddleWidth,
		paddleHeight
	};
	SDL_RenderFillRect(mRenderer, &paddleRight);
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

