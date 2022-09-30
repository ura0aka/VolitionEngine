#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class AnimationComponent
{
private:

	sf::Texture aTexture;
	std::vector<sf::IntRect> mFrames;

	float nHoldTime;
	int nFrames;

	int iFrame = 0;
	float iFrameTime = 0.0f;

public:

	AnimationComponent() = default;

	AnimationComponent(int x, int y, int width, int height, int framesnum, float holdtime, std::string&& spritesheet)
		: nHoldTime{holdtime}, nFrames{framesnum}
	{
		aTexture.loadFromFile(spritesheet);
		for (int i{ 0 }; i < nFrames; i++)
		{
			mFrames.emplace_back(sf::Vector2i{x,y},sf::Vector2i{width,height});
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
			if (++iFrame >= mFrames.size())
			{
				iFrame = 0;
			}
		}

	}

};