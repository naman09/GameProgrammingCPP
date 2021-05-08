#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Ship.h"
#include "BGSpriteComponent.h"

Game::Game() {
	mIsRunning = true;
	mTicksCount = 0;
	mWindow = nullptr;
	mRenderer = nullptr;
	mUpdatingActors = false;
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
	IMG_Init(IMG_INIT_PNG); //To use png images 
	return true; // success 
}

SDL_Texture* Game::LoadTexture(const char* filename) {
	SDL_Surface* surf = IMG_Load(filename);
	if (!surf) {
		SDL_Log("Failed to load texture file: %s", filename);
		return nullptr;
	}
	SDL_Texture* text = SDL_CreateTextureFromSurface(mRenderer, surf);
	SDL_FreeSurface(surf);
	if (!text) {
		SDL_Log("Failed to convert surface to texxture for: %s", filename);
		return nullptr;
	}
	return text;
}

SDL_Texture* Game::GetTexture(const char* filename) {
	std::string key{ filename };
	if (mFileTextureMap.find(key) == mFileTextureMap.end()) {
		mFileTextureMap[key] = LoadTexture(filename);
	}
	return mFileTextureMap[key];
}

void Game::LoadData() {
	//Add a ship
	Actor* ship = new Ship(this);
	AddActor(ship);

	Actor* genericActor = new Actor(this);

	BGSpriteComponent* back = new BGSpriteComponent(genericActor, 50); //drawn before others 
	BGSpriteComponent* back2 = new BGSpriteComponent(genericActor, 50);

	//different scroll speed for parallax effect
	back->SetScrollSpeed(10);
	back2->SetScrollSpeed(20);

	SDL_Texture* bg1Tex = GetTexture("Assets/Farback01.png");
	SDL_Texture* bg2Tex = GetTexture("Assets/Farback02.png");

	//SetTextures() -- ?
	back->SetBGTextures({ bg1Tex });
	back2->SetBGTextures({ bg2Tex });
	
	mSprites.push_back(back);
	mSprites.push_back(back2);
}

void Game::Shutdown() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
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
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	mUpdatingActors = true;

	for (Actor*& actor : mActors) {
		actor->UpdateActor(deltaTime);
	}
	while (!mPendingActors.empty()) {
		mActors.push_back(mPendingActors.back());
		mPendingActors.pop_back();
	}
	std::vector<Actor*> deadActors;
	for (Actor*& actor : mActors) {
		if (actor->GetState() == Actor::State::EDead) {
			deadActors.push_back(actor);
		}
	}
	for (Actor*& actor : deadActors) {
		delete actor;
	}
	for (auto& sprites : mSprites) {
		sprites->Update(deltaTime);
	}
}

void Game::GenerateOutput() {
	for (auto& sprite : mSprites) {
		sprite->Draw(mRenderer);
	}
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::AddActor(Actor* actor) {
	if (mUpdatingActors) {
		mPendingActors.push_back(actor);
	}
	else {
		mActors.push_back(actor);
	}
}

void Game::RemoveActor(Actor* actor) {
	while (!mActors.empty()) {
		delete mActors.back();
		mActors.pop_back(); //?
	}

}

void Game::AddSprite(SpriteComponent* sprite) {
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); iter++) {
		if ((*iter)->GetDrawOrder() > myDrawOrder) {
			break;
		}
	}
	mSprites.insert(iter, sprite);
}
