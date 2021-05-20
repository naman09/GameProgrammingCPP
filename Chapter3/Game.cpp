#include "Game.h"

Game::Game() : mIsRunning{ true }, mRenderer{ nullptr }, mTickCount{ 0 } {
}

void Game::Initialize() {}

void Game::ProcessInput() {}

void Game::UpdateGame() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount+16));
	float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
}

void Game::GenerateOutput() {}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown() {}
