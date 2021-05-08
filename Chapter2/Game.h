#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include "Actor.h"
#include "SpriteComponent.h"
#include <unordered_map>

class Game {
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	SDL_Window* mWindow;
	bool mIsRunning;
	bool mUpdatingActors;
	SDL_Renderer* mRenderer;
	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors; //new actors are added here
	std::vector<SpriteComponent*> mSprites;
	std::unordered_map<std::string, SDL_Texture*> mFileTextureMap;
	SDL_Texture* LoadTexture(const char* filename);
public:
	const int width{ 800 };
	const int height{ 600 };
	Uint32 mTicksCount;
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);
	void AddSprite(SpriteComponent* sprite); //insert sprite in sorted draw order
	SDL_Texture* GetTexture(const char* filename);
};
#endif