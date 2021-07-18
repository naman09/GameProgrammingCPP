#include "Game.h"
#include "Ship.h"
#include "AnimSpriteComponent.h"

Ship::Ship(Game* game) : Actor(game), mRightSpeed(0.0f), mDownSpeed(0.0f) {
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	asc->SetAnimTextures(anims);
	asc->SetAnimRun(true);
}

void Ship::UpdateActor(float deltaTime) {
	Actor::UpdateActor(deltaTime);
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	SetPosition(pos);
}

void Ship::ProcessKeyboard(const Uint8* state) {
	mDownSpeed = 0.0f;
	mRightSpeed = 0.0f;

	if (state[SDL_SCANCODE_W]) {
		mDownSpeed -= 100.0f;
	}
	if (state[SDL_SCANCODE_S]) {
		mDownSpeed += 100.0f;
	}
	if (state[SDL_SCANCODE_D]) {
		mRightSpeed += 100.0f;
	}
	if (state[SDL_SCANCODE_A]) {
		mRightSpeed -= 100.0f;
	}
}
