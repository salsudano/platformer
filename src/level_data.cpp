#include "level_data.h"
#include "object_shape.h"

#include "level_object.h"
#include "inactive_object.h"
#include "character_object.h"

#include "util\t_rect.h"
#include <SFML\Graphics.hpp>

const float DEFAULT_GRAVITY_X = 0.0;
const float DEFAULT_GRAVITY_Y = 1.0;

LevelData::LevelData(const ApplicationSettings& settings)
	: m_Gravity(DEFAULT_GRAVITY_X, DEFAULT_GRAVITY_Y)
	, m_Settings(settings)
	, m_Camera(settings)
{
}

LevelData::LevelData(const ApplicationSettings& settings, CharacterObject* pHero, const std::string& svgPath)
	: m_Gravity(DEFAULT_GRAVITY_X, DEFAULT_GRAVITY_Y)
	, m_Settings(settings)
	, m_Camera(settings)
{
	LoadLevel(pHero, svgPath);
}

LevelData::~LevelData()
{
	for (auto& layer : m_LevelDataLayers)
	{
		auto& lsLayerObjects = layer.second;
		for (auto& pLevelObject : lsLayerObjects)
		{
			if (pLevelObject != nullptr)
				delete pLevelObject;
			pLevelObject = nullptr;
		}
	}

	for (auto iter = m_Characters.begin(); iter != m_Characters.end(); ++iter)
	{
		std::vector<CharacterObject*>& lsCharacterObjects = iter->second;
		for (auto& pCharacterObject : lsCharacterObjects)
		{
			if (pCharacterObject != nullptr)
				delete pCharacterObject;
			pCharacterObject = nullptr;
		}
	}
}

const RTree<LevelObject>& LevelData::GetCollisionTree() const
{
	return m_LevelDataCollisionTree;
}

bool LevelData::LoadCharacter(CharacterObject* pCharacterObj)
{
	bool ret = false;

	if (pCharacterObj != nullptr)
		m_Characters[pCharacterObj->Type()].push_back(pCharacterObj);

	return ret;
}

bool LevelData::LoadLevel(CharacterObject* pHero, const std::string& svgPath)
{
	if (LoadSVGData(svgPath))
		return this->LoadCharacter(pHero);
	return false;
}

bool LevelData::LoadSVGData(const std::string& svgPath)
{
	SVGData* pSVGData = new SVGData(svgPath);
	if (pSVGData != nullptr)
	{
		const auto& lsLevelDataGroups = pSVGData->DataGroups();
		for (auto& svgDataGroup : lsLevelDataGroups)
			LoadSVGDataGroup(svgDataGroup);
		
		m_LevelRect.Normalize();
		m_Camera.FitToLevel(m_LevelRect);
		
		return true;
	}
	return false;
}

bool LevelData::LoadSVGDataGroup(const SVGGroup* pDataGroup, const SVGGroup* pParentGroup /*= nullptr*/)
{
	bool ret = true;
	
	if (pDataGroup != nullptr)
	{
		const std::vector<SVGElement*>& lsGroupElements = pDataGroup->Elements();
		for (unsigned int i = 0; ret && (i < lsGroupElements.size()); ++i)
			ret &= LoadSVGDataElement(lsGroupElements[i], pDataGroup);

		const std::vector<SVGGroup*>& lsLevelDataSubGroups = pDataGroup->DataGroups();
		for (unsigned int i = 0; i < lsLevelDataSubGroups.size(); ++i)
			ret &= LoadSVGDataGroup(lsLevelDataSubGroups[i], pDataGroup);
	}

	return ret;
}

LevelData::LayerType LevelData::GetLevelDataGroupFromDescription(const std::string& layerDescription) const
{
	if		(layerDescription == "Bounds")		return LayerType::Boundary;
	else if (layerDescription == "Background")	return LayerType::Background;
	else if (layerDescription == "Foreground")	return LayerType::Foreground;
	else if (layerDescription == "Platforms")	return LayerType::Platforms;

	return LayerType::Invalid;
}

bool LevelData::LoadSVGDataElement(const SVGElement* pSVGElement, const SVGGroup* pGroup, const std::string childType /* ="" */)
{
	bool ret = false;
	
	if ((pSVGElement != nullptr) && (pGroup != nullptr))
	{
		LevelObject* pLevelObj = nullptr;
		
		LayerType elemLayer = GetLevelDataGroupFromDescription(pGroup->LayerType());
		switch (elemLayer)
		{
			case LayerType::Invalid:
			default:
				// If this group wasn't determined to be in a valid layer, check 
				// if it's a sub-group of some other valid level layer. If so,  
				// load its elements into the parent's level layer.
				ret = LoadSVGDataElement(pSVGElement, pGroup->ParentGroup(), pGroup->LayerType());
				break;

			case LayerType::Background:
			case LayerType::Boundary:
			case LayerType::Foreground:
			case LayerType::Platforms:
				if (elemLayer == LayerType::Background)
					pLevelObj = new BackgroundLevelObject(pSVGElement->CloneShape());
				else
					pLevelObj = new InactiveLevelObject(pSVGElement->CloneShape());

				if (pLevelObj != nullptr)
				{
					const std::string& type = (childType.length() > 0) ? childType : pGroup->LayerType();
					pLevelObj->SetDescription(type);
					ret = (type.length() > 0);
				}
				break;			
		}

		if ((elemLayer != LayerType::Invalid) && (pLevelObj != nullptr))
		{
			m_LevelDataLayers[elemLayer].push_back(pLevelObj);
			if (elemLayer == LayerType::Platforms)
				m_LevelDataCollisionTree.Insert(pLevelObj);
			
			if (m_LevelRect.IsEmpty())
				m_LevelRect = pLevelObj->BoundingBox();
			m_LevelRect.Include(pLevelObj->BoundingBox());
		}
	}

	return ret;
}

int LevelData::ProcessInput()
{
	int ret = 0;

	m_Camera.ProcessInput();

	// TODO: add menu controls here, and remove separate menu update in DataManager::ProcessInput?
	const std::vector<CharacterObject*> lsPlayableCharacters = m_Characters[CharacterType::Controllable];
	for (auto& pCharacter : lsPlayableCharacters)
		pCharacter->ProcessInput();

	return ret;
}

int LevelData::Update()
{
	int ret = 0;

	for (auto& layer : m_LevelDataLayers)
	{
		const LayerType layerType = layer.first;
		const std::vector<LevelObject*>& lsLayerObjects = layer.second;
		for (auto& pObject : lsLayerObjects)
			pObject->Update(this);
	}

	for (auto& characterGroup : m_Characters)
	{
		const CharacterType type = characterGroup.first;
		const std::vector<CharacterObject*>& lsCharacters = characterGroup.second;
		for (auto& pCharacter : lsCharacters)
		{
			pCharacter->Update(this);
			if (type == CharacterType::Controllable)
				m_Camera.Update(pCharacter, m_LevelRect);
		}
	}

	return ret;
}

int LevelData::Render(sf::RenderWindow& window)
{
	int ret = 0;

//  Render the collision bounds tree
//	this->m_LevelSpatialBounds.Render(window);
	
	// World/Level objects
	for (auto& iter = m_LevelDataLayers.begin(); iter != m_LevelDataLayers.end(); ++iter)
	{
		const LayerType layer = iter->first;
		const std::vector<LevelObject*>& lsObjects = iter->second;

		for (auto& pObject : lsObjects)
			ret += pObject->Render(window);
	}

	// Character ojbects
	for (auto& iter = m_Characters.begin(); iter != m_Characters.end(); ++iter)
	{
		const CharacterType type = iter->first;
		const std::vector<CharacterObject*>& lsCharacters = iter->second;

		for (auto& pCharacter : lsCharacters)
			pCharacter->Render(window);
	}
	
	// Assign viewport
	window.setView(m_Camera);

	return ret;
}

const Camera& LevelData::GetCamera() const
{
	return m_Camera;
}

const TPoint<float>& LevelData::Gravity() const
{
	return m_Gravity; 
}

sf::RectangleShape LevelData::BoundingRectangleShape() const
{
	sf::Vector2f levelWorldSize(m_LevelRect.Width(), m_LevelRect.Height());

	sf::RectangleShape rect;
	rect.setSize(levelWorldSize);
	rect.setPosition(m_LevelRect.PtA().x, m_LevelRect.PtA().y);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(10);
	return rect;
}

