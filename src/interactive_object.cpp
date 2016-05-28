#include "interactive_object.h"
#include "level_data.h"

InteractiveObject::InteractiveObject() 
{
	SetDescription("interactive");
}
	
InteractiveObject::~InteractiveObject() 
{ 
}

bool InteractiveObject::Update(const LevelData* pLevelData)
{
	return false;
}

CementBlockObject::CementBlockObject()
{
}

CementBlockObject::CementBlockObject(const float x)
{
	SetDescription("cement");
}

CementBlockObject::~CementBlockObject() 
{
}

