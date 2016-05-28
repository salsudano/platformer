#include "inactive_object.h"
#include "level_data.h"

	BackgroundLevelObject::BackgroundLevelObject() 
	{
		SetDescription("background");
	}

	BackgroundLevelObject::BackgroundLevelObject(ObjectShape* pShape)
		: InactiveLevelObject(pShape)
	{ 
		SetDescription("background");
	}

	BackgroundLevelObject::~BackgroundLevelObject() 
	{
	}

	int BackgroundLevelObject::Update(LevelData* pLevelData)
	{
		const Camera& cam = pLevelData->GetCamera();
		const TPoint<float>& center = cam.getCenter();
		const TPoint<float>& origin = cam.GetOrigin();

		float update = origin.x - center.x;
		this->SetXPosition(this->GetXPosition() + update);
		return 0;
	}