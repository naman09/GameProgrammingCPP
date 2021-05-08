#include "Game.h"
#include "Ship.h"
#include "AnimSpriteComponent.h"

Ship::Ship(Game* game) : Actor(game) {
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime) {
	Actor::UpdateActor(deltaTime);
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	SetPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t* state) {
	mDownSpeed = 0.0f;
	mRightSpeed = 0.0f;

	if (state[SDL_SCANCODE_W]) {
		mDownSpeed -= 1.0f;
	}
	if (state[SDL_SCANCODE_S]) {
		mDownSpeed += 1.0f;
	}
	if (state[SDL_SCANCODE_D]) {
		mRightSpeed += 1.0f;
	}
	if (state[SDL_SCANCODE_A]) {
		mRightSpeed -= 1.0f;
	}
}
