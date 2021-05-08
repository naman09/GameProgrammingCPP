#include "BGSpriteComponent.h"

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures) {
	int count = 0;
	for (auto& tex : textures) {
		BGTexture temp;
		temp.mTexture = tex;
		temp.mOffset.x = count * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.push_back(temp);
		count++;
	}
}

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder) 
	: SpriteComponent(owner, drawOrder) {
	mScreenSize.x = 100.0f; //TODO
	mScreenSize.y = 200.0f; //TODO

	mScrollSpeed = 10.0f;
}

void BGSpriteComponent::Update(float deltaTime) {
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures) {
		bg.mOffset.x += mScrollSpeed * deltaTime;

		//if this is completely off the screen then reset offset
		if (bg.mOffset.x < -mScreenSize.x) { 
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer) {

}
