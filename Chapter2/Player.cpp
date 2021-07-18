#include "Player.h"
#include "Game.h"
#include <iostream>

Player::Player(Game* game) : Actor(game), moveRight(0.0f), moveUp(0.0f) {
	game->AddActor(this);
	moveAnim = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> vec{
		game->GetTexture("Assets/Character01.png"),
		game->GetTexture("Assets/Character02.png"),
		game->GetTexture("Assets/Character03.png"),
		game->GetTexture("Assets/Character04.png"),
		game->GetTexture("Assets/Character05.png"),
		game->GetTexture("Assets/Character06.png")
	};
	moveAnim->SetAnimTextures(vec);
	moveAnim->SetAnimeFPS(6);

	jumpAnim = new AnimSpriteComponent(this, 100, false);
	vec = {
		game->GetTexture("Assets/Character01.png"),
		game->GetTexture("Assets/Character07.png"),
		game->GetTexture("Assets/Character08.png"),
		game->GetTexture("Assets/Character09.png"),
		game->GetTexture("Assets/Character10.png"),
		game->GetTexture("Assets/Character11.png"),
		game->GetTexture("Assets/Character12.png"),
		game->GetTexture("Assets/Character13.png"),
		game->GetTexture("Assets/Character14.png"),
		game->GetTexture("Assets/Character15.png"),
	};
	jumpAnim->SetAnimTextures(vec);
	jumpAnim->SetAnimeFPS(6);
}

void Player::UpdateActor(float deltaTime) {
	Actor::UpdateActor(deltaTime);
	Vector2 currentPos = GetPosition();
	currentPos.x += moveRight;
	currentPos.y -= moveUp;
	SetPosition(currentPos);
}

void Player::ProcessKeyboard(const uint8_t* state) {
	moveRight = 0.0f;
	moveAnim->SetAnimRun(false);
	if (state[SDL_SCANCODE_RIGHT]) {
		moveAnim->SetAnimRun(true);
		moveRight += 1.0f;
	}
	if (state[SDL_SCANCODE_SPACE] && !jumpAnim->GetAnimRun()) {
		jumpAnim->SetAnimRun(true);
		if (jumpAnim->GetCurrFrame() >= 3) {
			std::cout << "Here" << std::endl;
			moveUp = std::max(0.0f, moveUp - 1.0f);
		}
		else {
			std::cout << "Here2" << std::endl;
			moveUp += 1.0f;
		}
	}
	if (moveUp <= 0.0f && jumpAnim->GetAnimRun()) {
		jumpAnim->SetAnimRun(false);
		moveUp = 0.0f;
	}
}
