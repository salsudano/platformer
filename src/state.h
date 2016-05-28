#ifndef __STATE_H
#define __STATE_H

#include <string>
#include <SFML\Graphics.hpp>

class Object;

class State
{
public:
					State();
	virtual		   ~State();

	virtual	bool	Update(Object* pObject) = 0;
	
	sf::Sprite&		GetSprite();

protected:
	bool			AddTexture(const std::string& texturePath);
	bool			SetNextTexture();

private:
	bool			LoadSprite();

public:
	std::string					m_Description;			// Description (for debugging)

protected:
	sf::Sprite					m_Sprite;				// Sprite (texture + rect)
	std::vector<sf::Texture>	m_lsTextures;			// Texture (per state)
	std::string					m_TexturePath;			// Where to find the textures for this state
	sf::Vector2f				m_DistanceMoved;		// Distance moved since last texture update
	sf::Vector2f				m_MaxVelocity;			// Maximum velocity for X and Y axis
	sf::Vector2f				m_MinVelocity;			// Minimum velocity for X and Y axis
	sf::Vector2f				m_Acceleration;			// Acceleration values for X and Y axis
	sf::Vector2f				m_Deceleration;			// Deceleration values for X and Y axis

private:
	bool						m_IsActive;				// Is this state currently active?
	int							m_CurrentTextureIndex;	// Index of the current texture
};

#endif //__STATE_H