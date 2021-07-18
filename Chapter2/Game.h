#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include <unordered_map>
#include "Player.h"

class Game {
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	SDL_Texture* LoadTexture(const char* filename);

	SDL_Window* mWindow;
	bool mIsRunning;
	bool mUpdatingActors;
	SDL_Renderer* mRenderer;
	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors; //new actors are added here
	std::vector<SpriteComponent*> mSprites;
	std::unordered_map<std::string, SDL_Texture*> mFileTextureMap;
public:
	const float width{ 800.0f };
	const float height{ 600.0f };
	Uint32 mTicksCount;

	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);
	void AddSprite(SpriteComponent* sprite); //insert sprite in sorted draw order
	void RemoveSprite(SpriteComponent* sprite);
	SDL_Texture* GetTexture(const char* filename);
	void LoadData();

	//Game specific
	Ship* mShip;
	Player* mPlayer;
};
#endif