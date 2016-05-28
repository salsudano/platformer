#ifndef __LEVEL_DATA_H
#define __LEVEL_DATA_H

#include <unordered_map>

#include <SFML\Graphics.hpp>

#include "util\t_tree.h"
#include "util\svg_data.h"

#include "camera.h"
#include "data_component.h"
#include "game_object_defs.h"

class GameObject;
class LevelObject;
class CharacterObject;

enum class CharacterType;

class LevelData
{
public:
	enum class LayerType
	{
		Invalid,
		
		Boundary,				// Level / Player boundaries
		//LevelBounds,			// Level / Player boundaries
		
		Background,			
		//Background1,			// Closest background
		//Background2,			// Middle background
		//Background3,			// Furthest background
		
		Foreground,
		//Foreground1,			// Closest foreground
		//Foreground2,			// Middle foreground
		//Foreground3,			// Furthest foreground

		Platforms,
		//SolidPlatforms,			//Can't be passed through
		//OpenFloorPlatforms,		// Can be passed through from the top
		//OpenCeilingPlatforms,		// Can be passed through from the bottom
		//OpenLeftWallPlatforms,	// Can be passed through from the left only
		//OpenRightWallPlatforms	// Can be passed through from the right only
	};
	
public:
				LevelData(const ApplicationSettings& settings);
				LevelData(const ApplicationSettings& settings, CharacterObject* pHero, const std::string& svgPath);
	virtual	   ~LevelData();

	int			Update();
	int			ProcessInput();
	int			Render(sf::RenderWindow& window);

	bool		LoadLevel(CharacterObject* pHero, const std::string& svgPath);
	bool		LoadSVGData(const std::string& svgPath);
	bool		LoadCharacter(CharacterObject* pCharacterObj);

	sf::RectangleShape			BoundingRectangleShape() const;
	LayerType					GetLevelDataGroupFromDescription(const std::string& descr) const;

	const TPoint<float>&		Gravity() const;

	const Camera&				GetCamera()		   const;
	const RTree<LevelObject>&	GetCollisionTree() const;
	
private:
	bool		LoadSVGDataGroup(const SVGGroup* pDataGroup, const SVGGroup* pParentGroup = nullptr);
	bool		LoadSVGDataElement(const SVGElement* pDataElement, const SVGGroup* pDataGroup, const std::string name = "");

private:
	const ApplicationSettings&				 m_Settings;

	Camera									 m_Camera;
											 
	TRect<float>							 m_LevelRect;
	TPoint<float>							 m_Gravity;

	RTree<LevelObject>						 m_LevelDataCollisionTree;

	std::unordered_map<CharacterType,		 std::vector<CharacterObject*> >  m_Characters;
	std::unordered_map<LevelData::LayerType, std::vector<LevelObject*>	   >  m_LevelDataLayers;

};

#endif // __LEVEL_DATA_H
