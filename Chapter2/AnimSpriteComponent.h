#ifndef ANIM_SPRITE_COMPONENT_H
#define ANIM_SPRITE_COMPONENT_H

#include <vector>
#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent {
	std::vector<SDL_Texture*> mAnimTextures; //All textures in the animation
	float mCurrFrame; //current frame displayed
	float mAnimFPS; // animation frame rate
public: 
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	void Update(float deltaTime) override;
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures) { mAnimTextures = textures; }
	float GetAnimFPS() const { return mAnimFPS; }
};

#endif