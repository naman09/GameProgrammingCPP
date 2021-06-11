#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* actor, int drawOrder) 
	: Component(actor), mDrawOrder(drawOrder), mTexture(nullptr), mTextHeight(0), mTextWidth(0) {}


void SpriteComponent::SetTexture(SDL_Texture* texture) {
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTextWidth, &mTextHeight);
}