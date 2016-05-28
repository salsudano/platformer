#include "level_object.h"

LevelObject::LevelObject()
{
	this->SetDescription("level_object");
}

LevelObject::LevelObject(ObjectShape* pShape)
	: ShapeObject(pShape)
{
	this->SetDescription("level_object");
}

LevelObject::~LevelObject()
{
}

int LevelObject::ProcessInput()
{
	return 0;
}

int LevelObject::Update(LevelData* pLevelData)
{
	return 0;
}

int	LevelObject::Render(sf::RenderWindow& window)
{
	return ShapeObject::Render(window);
}

