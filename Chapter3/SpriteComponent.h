#ifndef SPRTIE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Component.h"

class SpriteComponent : public Component {
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTextHeight;
	int mTextWidth;
public:
	SpriteComponent(Actor* actor, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);
	int GetDrawOrder() { return mDrawOrder; }
	int GetTextHeight() { return mTextHeight; }
	int GetTextWidth() { return mTextWidth; }
};

#endif
