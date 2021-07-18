#ifndef ANIM_SPRITE_COMPONENT_H
#define ANIM_SPRITE_COMPONENT_H

#include <vector>
#include "SpriteComponent.h"
#include <string>

class AnimSpriteComponent : public SpriteComponent {
	std::vector<SDL_Texture*> mAnimTextures; //All textures in the animation
	float mCurrFrame; //current frame displayed
	float mAnimFPS; // animation frame rate
	bool mLooping;
	bool mAnimRun; //by default anim will be in stop state
public: 
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100, bool looping = true, bool animRun = false);
	void Update(float deltaTime) override;
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimeFPS(const float& animFPS) { mAnimFPS = animFPS; }
	void SetAnimRun(const bool& animRun) { mAnimRun = animRun; }
	bool GetAnimRun() const { return mAnimRun; }
	float GetCurrFrame() const { return mCurrFrame; }
};

#endif