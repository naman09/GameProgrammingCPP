#include "SpriteComponent.h"

void SpriteComponent::SetTexture(SDL_Texture* texture) {
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

double MathToDegrees(float angleRadians) {
	double pi = acos(-1);
	return angleRadians * 180 / pi;
}

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) 
	: Component(owner, drawOrder) {}

SpriteComponent::~SpriteComponent() {}

void SpriteComponent::Draw(SDL_Renderer* renderer) {
	if (mTexture) {
		SDL_Rect r;
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);
		SDL_RenderCopyEx(renderer,
			mTexture, 
			nullptr, //part of rectangle in texture to draw
			&r, // destination rectange
			-MathToDegrees(mOwner->GetRotation()),  
			nullptr, //rotation about center
			SDL_FLIP_NONE
		);
	}
}