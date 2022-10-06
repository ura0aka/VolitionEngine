#pragma once

#include "ResourceManager.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"


class AnimationComponent
{
private:
	// TODO: Fix resource manager later
	std::shared_ptr<sf::Texture> aTexture;
	std::vector<sf::IntRect> mFrames;
	ResourceManager mResMan;

	float nHoldTime;
	int nFrames;

	int iFrame = 0;
	float iFrameTime = 0.0f;

public:

	AnimationComponent() = default;


	AnimationComponent(int x, int y, int width, int height, int framesnum, float holdtime, std::string&& spritesheet)
		: nHoldTime{ holdtime }, nFrames{ framesnum }
	{
		// iterate over the vector of rects 
		// (each animation component object instance has a different animation loop)
		mFrames.reserve(nFrames);
		aTexture = mResMan.getTexture(spritesheet);
		for (int i{ 0 }; i < nFrames; ++i)
		{
			mFrames.emplace_back(sf::Vector2i{ x,y }, sf::Vector2i{ width,height });
			x += width;
		}
	}

	void animateSprite(sf::Sprite& spr) const
	{
		spr.setTexture(*aTexture);
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