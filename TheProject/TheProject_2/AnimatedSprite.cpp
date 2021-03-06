#include "AnimatedSprite.h"
#include <iostream>
#include <vector>

namespace TheProject
{
	AnimatedSprite::AnimatedSprite(const std::vector<std::string> spriteSheetLocations, const sf::Vector2f& pos, float speed)
		: m_speed{speed}, m_spriteSheets{std::vector<sf::Texture>{}}, m_pos{pos}, m_vel{sf::Vector2f{0.f, 0.f}}, m_currentFrameIndex{0},
		  m_currentAnimation{NONE}, m_animations{std::map<EAnimation, Animation>{}}, m_elapsedSeconds{0}, 
		  m_lines{std::vector<sf::RectangleShape>{sf::RectangleShape{}, sf::RectangleShape{}, sf::RectangleShape{}, sf::RectangleShape{}}}, 
		  m_drawBounds{true}, m_scaleFactor{2.f}, m_boundingBoxColor(sf::Color::Blue)
	{
		// Create / Load SpriteSheet Textures
		for (std::string s : spriteSheetLocations)
		{
			sf::Texture tex{};
			tex.loadFromFile(s);
			m_spriteSheets.push_back(tex);
		}

		// Default Spritesheet is first
		if (!m_spriteSheets.empty())
			m_sprite = sf::Sprite{ m_spriteSheets[0] };
		m_sprite.setScale(m_scaleFactor, m_scaleFactor);
	}

	AnimatedSprite::~AnimatedSprite()
	{
		
	}

	void AnimatedSprite::update(float deltaTime)
	{
		m_pos += m_vel * deltaTime;
		m_sprite.setPosition(m_pos);
		playAnimation(deltaTime);
	}

	void AnimatedSprite::addAnimation(EAnimation name, int indexSpriteSheet, int frameWidth, int frameHeight, int yRow, int xCol,
		int numFrames, float frameDelay, bool mirror, bool reverse)
	{
		if (indexSpriteSheet < 0 || indexSpriteSheet >= m_spriteSheets.size())
		{
			std::cout << "@AnimatedSprite.addAnimation(): indexSpriteSheet is invalid!" << std::endl;
			return;
		}
		std::vector<sf::Rect<int>> frames;

		int frame = 0;
		int spriteSheetWidth = m_spriteSheets[indexSpriteSheet].getSize().x;

		while(frame++ < numFrames)
		{
			if ((xCol * frameWidth) == spriteSheetWidth)
			{
				yRow++;
				xCol = 0;
			}
			frames.push_back(sf::Rect<int>{ xCol++ * frameWidth, yRow * frameHeight, frameWidth, frameHeight});
		}

		m_animations[name] = Animation{ indexSpriteSheet, frames, frameDelay, mirror, reverse };
	}

	void AnimatedSprite::playAnimation(float deltaTime)
	{
		if (m_currentAnimation == NONE)
			return;

		Animation currentAnimation = m_animations[m_currentAnimation];

		if (currentAnimation.reverse)
		{
			if (m_currentFrameIndex < 0)
				m_currentFrameIndex = currentAnimation.frames.size() - 1;

			if (m_elapsedSeconds > currentAnimation.frameDelay)
			{
				m_sprite.setTextureRect(currentAnimation.frames[m_currentFrameIndex--]);
				m_elapsedSeconds = 0;
			}
		}
		else
		{
			if (m_currentFrameIndex > currentAnimation.frames.size() - 1)
				m_currentFrameIndex = 0;

			if (m_elapsedSeconds > currentAnimation.frameDelay)
			{
				m_sprite.setTextureRect(currentAnimation.frames[m_currentFrameIndex++]);
				m_elapsedSeconds = 0;
			}
		}
		m_elapsedSeconds += deltaTime;
	}

	void AnimatedSprite::setAnimation(EAnimation name)
	{
		if (m_currentAnimation == name || m_animations.count(name) == 0)
			return;

		m_currentAnimation = name;
		Animation currentAnimation = m_animations[m_currentAnimation];

		m_sprite.setTexture(m_spriteSheets[currentAnimation.indexSpriteSheet]);
		m_sprite.setTextureRect(currentAnimation.frames[0]);

		currentAnimation.mirror ? m_sprite.setScale(-1.f * m_scaleFactor, m_scaleFactor) : 
		m_sprite.setScale(m_scaleFactor, m_scaleFactor);
	}
}
