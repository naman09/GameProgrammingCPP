#include "AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder, bool looping, bool animRun)
	: SpriteComponent(owner, drawOrder), mCurrFrame(0.0f), mAnimFPS(24.0f), 
	mLooping(looping), mAnimRun(animRun) {}

void AnimSpriteComponent::Update(float deltaTime) {
	SpriteComponent::Update(deltaTime);
	if (!mAnimRun) {
		mCurrFrame = 0.0f; //resets the anim if it will run again
		SetTexture(mAnimTextures[0]);
		return;
	}
	if (mAnimTextures.size() > 0) {
		mCurrFrame += mAnimFPS * deltaTime;
	}
	
	while (mCurrFrame >= mAnimTextures.size()) {
		if (!mLooping) {
			return; //Animation ends
		}
		mCurrFrame -= mAnimTextures.size();
	}
	SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures) {
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0) {
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}
