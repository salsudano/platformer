#include <util\t_rect.h>
#include <SFML\Window.hpp>

#include "camera.h"
#include "application_settings.h"
#include "character_object.h"

Camera::Camera(const ApplicationSettings& settings)
	: m_bZooming(false)
	, m_Settings(settings)
{ }

Camera::~Camera()
{
}

const TPoint<float>& Camera::GetOrigin() const
{
	return m_OriginPt;
}

bool Camera::FitToLevel(const TRect<int>& levelRect)
{
	this->setCenter(static_cast<float>(levelRect.Center().x), 
					static_cast<float>(levelRect.Center().y));
	
	const sf::VideoMode& res = m_Settings.Display.Resolution();
	const float windowRatio = static_cast<float>(res.width) / static_cast<float>(res.height);

	float width  = static_cast<float>(levelRect.Width())  / 2.0f;
	float height = static_cast<float>(levelRect.Height()) / 2.0f;

	float viewRatio = width / height;
	while (windowRatio > viewRatio)
	{
		height -= 1;
		viewRatio = width / height;
	}
	
	while (windowRatio < viewRatio)
	{
		width -= 1.0f;
		viewRatio = width / height;
	}

	if (width > Camera::MAX_VIEWPORT_WIDTH || height > Camera::MAX_VIEWPORT_HEIGHT)
	{
		width  = Camera::MAX_VIEWPORT_WIDTH;
		height = Camera::MAX_VIEWPORT_HEIGHT;
	}
	else if (width < Camera::MIN_VIEWPORT_WIDTH || height < Camera::MIN_VIEWPORT_HEIGHT)
	{
		width  = Camera::MIN_VIEWPORT_WIDTH;
		height = Camera::MIN_VIEWPORT_HEIGHT;
	}

	this->setSize(width, height);
	return true;
}

int Camera::ProcessInput()
{
	int ret = 0;

	// Zoom in (+)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
	{
		ret += 1;
		if (!m_bZooming)
			zoom(0.9f);
		m_bZooming = true;
	}
	// Zoom out (-)
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
	{
		ret += 1;
		if (!m_bZooming)
			zoom(1.1f);
		m_bZooming = true;
	}
	else
	{
		m_bZooming = false;

	// TODO: enable viewport movement in debug mode
	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->setCenter(getCenter().x, getCenter().y - 1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->setCenter(getCenter().x, getCenter().y + 1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->setCenter(getCenter().x - 1, getCenter().y);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->setCenter(getCenter().x + 1, getCenter().y);
	*/
	}

	return ret;
}

int	Camera::Update(const CharacterObject* pCharacterObj, const TRect<float> levelRect)
{
	const sf::Vector2<float>& origCenter = this->getCenter();
	if ((pCharacterObj != nullptr) && pCharacterObj->CameraFocus())
	{
		const TPoint<float>& characterPt = pCharacterObj->GetPosition();
		if (pCharacterObj->HasComponent(Component::Type::State))
		{
			TPoint<float> newViewCenter = origCenter;

			const sf::Vector2f& viewportSize = this->getSize();
			const sf::Rect<int>& textureRect = pCharacterObj->GetStateComponent()->CurrentState()->GetSprite().getTextureRect();
			
			TRect<float> viewportRect  = TRect<float>(this->getCenter(), viewportSize.y, viewportSize.x, Rect::Center);
			TRect<float> characterRect = TRect<float>(characterPt, textureRect.height, textureRect.width, Rect::TopLeftCorner);

			// If the character isn't contained within the viewport 
			// rect, center the viewport on the character's position
			if (!viewportRect.Contains(characterRect))
			{
				newViewCenter = characterRect.Center();
				viewportRect.SetCenter(newViewCenter);
			}

			TRect<float> playerFocusRect = viewportRect.Rescale(0.65f, 0.50f, Rect::Center);
			if (!playerFocusRect.Contains(characterRect))
			{
				// Move the rescaled view rect to contain the player focus rect
				playerFocusRect.MoveToContain(characterRect);
				newViewCenter = playerFocusRect.Center();
				viewportRect.SetCenter(newViewCenter);
			}

			if (!levelRect.Contains(viewportRect))
			{
				// Move the view rect within the level bounds
				viewportRect.MoveToBeContainedIn(levelRect);
				newViewCenter = viewportRect.Center();
			}
					
			this->setCenter(newViewCenter.x, newViewCenter.y);

			if (m_OriginPt.IsEmpty())
				m_OriginPt = newViewCenter;

		}
	}

	return (origCenter != this->getCenter());
}

