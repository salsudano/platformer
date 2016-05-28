#ifndef __OBJECT_STATE_H
#define __OBJECT_STATE_H

#include "util\t_rect.h"
#include "game_object_defs.h"

#include <SFML\Audio.hpp>

template <typename TAction>
class ObjectState
{
public:

	ObjectState()
		: m_IsActive(false)
		, m_CurrentTextureIndex(0)
	{ }

	virtual ~ObjectState()
	{ 
	}

	virtual bool PreActivate()
	{
		return true;
	}

	virtual bool Activate()
	{
		assert(!m_IsActive);
		this->PreActivate();

		m_CurrentTextureIndex = 0;
		if (m_lsTextures.size() > 0)
		{
			m_IsActive = this->SetNextTexture();
			return m_IsActive;
		}

		return false;
	}

	virtual bool Deactivate()
	{
		m_IsActive = false;
		return true;
	}

	virtual bool IsActive() const
	{
		return m_IsActive;
	}

	sf::Sprite& GetSprite()
	{ 
		return m_Sprite; 
	}

	const TAction Action() const
	{
		return m_Action;
	}

	void Action(const TAction action)
	{
		m_Action = action;
	}

protected:
	bool AddTexture(const std::string& texturePath)
	{
		sf::Texture texture;
		std::cout << "Loading: " << texturePath << std::endl;
		if (texture.loadFromFile(texturePath))
		{
			m_TexturePath = texturePath;
			m_lsTextures.push_back(texture);
			m_Sprite.setTexture(texture);
			return true;
		}
		return false;
	}
	
	bool SetNextTexture()
	{
		m_Sprite.setTexture(m_lsTextures[m_CurrentTextureIndex]);
		m_CurrentTextureIndex++;
		m_CurrentTextureIndex %= m_lsTextures.size();
		return true;
	}

protected:
	sf::Sprite					m_Sprite;				// Sprite (texture + rect)
	sf::Sound					m_Sound;				// Sound triggered by this state activaing 
	TAction						m_Action;				// Action that defines this state (moving, still, jumping, crouching, etc..)
	std::vector<sf::Texture>	m_lsTextures;			// Texture (per state)
	std::string					m_TexturePath;			// Where to find the textures for this state
	TPoint<float>				m_DistanceMoved;		// Distance moved since last texture update

private:
	bool						m_IsActive;				// Is this state currently active?
	int							m_CurrentTextureIndex;	// Index of the current texture
};


#endif // __OBJECT_STATE_H