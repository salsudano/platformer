#ifndef __CAMERA_H
#define __CAMERA_H

#include <SFML/Graphics.hpp>

class CharacterObject;
class ApplicationSettings;

template <typename T> class TRect;

class Camera : public sf::View
{
public:
					Camera(const ApplicationSettings& settings);
				   ~Camera();

	int				ProcessInput();
	int				Update(const CharacterObject* pCharacter, const TRect<float> levelRect);

	bool					FitToLevel(const TRect<int>& levelRect);
	const TPoint<float>&	GetOrigin() const;

private:
	const ApplicationSettings&	m_Settings;
	
	bool						m_bZooming;
	TPoint<float>				m_OriginPt;

	// TODO: Force to current window size or resolution...
	static const int MIN_VIEWPORT_WIDTH  = 800;
	static const int MAX_VIEWPORT_WIDTH  = MIN_VIEWPORT_WIDTH * 2;
	static const int MIN_VIEWPORT_HEIGHT = 600;
	static const int MAX_VIEWPORT_HEIGHT = MIN_VIEWPORT_HEIGHT * 2;
};

#endif // __CAMERA_H
