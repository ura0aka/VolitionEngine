#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class AnimationComponent
{
private:

	static constexpr int nFrames = 12;
	static constexpr float nHoldTime = 0.07f;
	int iFrame = 0;
	float iFrameTime = 0.0f;

	sf::Texture aTexture;
	sf::IntRect mFrames[nFrames];
	
public:

	AnimationComponent() = default;
	
	AnimationComponent(int x, int y, int width, int height, std::string&& spritesheet)
	{
		aTexture.loadFromFile(spritesheet);
		for (int i{ 0 }; i < nFrames; i++)
		{
			mFrames[i] = { x + i * width, y, width, height};
		}
	}

	void animateSprite(sf::Sprite& spr) const
	{
		spr.setTexture(aTexture);
		spr.setTextureRect(mFrames[iFrame]);
	}

	void updateAnimation(const float& dt)
	{
		iFrameTime += dt;
		while (iFrameTime >= nHoldTime)
		{
			iFrameTime -= nHoldTime;
			if (++iFrame >= nFrames)
			{
				iFrame = 0;
			}
		}

	}

};