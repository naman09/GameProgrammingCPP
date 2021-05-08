#ifndef BG_SPRITE_COMPONENT_H
#define BG_SPRITE_COMPONENT_H 

#include <vector>
#include "SpriteComponent.h"
#include "Vector2.h"

class BGSpriteComponent : public SpriteComponent {
	struct BGTexture {
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};

	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;

public:
	BGSpriteComponent(class Actor* owner, int drawOrder = 100);
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }

};

#endif
