#include "physics_component.h"
#include "game_object.h"
#include "character_object.h"
#include "level_data.h"
#include "level_object.h"

PhysicsComponent::PhysicsComponent() 
	: Component(Component::Type::Physics)
{
}

PhysicsComponent::~PhysicsComponent() 
{
}

int PhysicsComponent::Update(CharacterObject* pGameObject, LevelData* pLevelData) const
{
	bool ret = (pGameObject != nullptr && pLevelData != nullptr);
	if (ApplyLevelPhysics(pGameObject, pLevelData) && ClampVelocity(pGameObject))
	{
		ret &= UpdatePosition(pGameObject);
		ret &= ResolveCollisions(pGameObject, pLevelData->GetCollisionTree());
	}
	return ret;
}

bool PhysicsComponent::ApplyLevelPhysics(CharacterObject* pGameObject, const LevelData* pLevelData) const
{
	// Apply gravity if the object isn't touching the ground
	if (!pGameObject->TouchingGround())
	{
		const float yGravity = pLevelData->Gravity().y;
		pGameObject->SetYVelocity(pGameObject->GetYVelocity() + yGravity);
	}
	return true;
}

bool PhysicsComponent::ClampVelocity(CharacterObject* pObject) const
{
	if (pObject != nullptr)
	{
		const sf::Vector2<float>& curVelocity = pObject->GetVelocity(GameObject::Velocity::Current);
		const sf::Vector2<float>& maxVelocity = pObject->GetVelocity(GameObject::Velocity::Max);

		if (fabs(curVelocity.x) > maxVelocity.x)
		{
			const float clampedXVelocity = (curVelocity.x > 0.0f) ? maxVelocity.x : -maxVelocity.x;
			pObject->SetXVelocity(clampedXVelocity);
		}
		if (fabs(curVelocity.y) > maxVelocity.y)
		{
			const float clampedYVelocity = (curVelocity.y > 0.0f) ? maxVelocity.y : -maxVelocity.y;
			pObject->SetYVelocity(clampedYVelocity);
		}
		return true;
	}
	return false;
}

bool PhysicsComponent::UpdatePosition(CharacterObject* pCharacterObj) const
{
	const      TPoint<float>& currPosition = pCharacterObj->GetPosition();
	const sf::Vector2<float>& currVelocity = pCharacterObj->GetVelocity();
	const sf::Vector2<float>  newPosition  = currPosition + currVelocity;

	pCharacterObj->SetPosition(newPosition);
	return true;
}

bool PhysicsComponent::ResolveCollisions(CharacterObject* pCharacterObj, const RTree<LevelObject>& objectBoundsTree) const
{
	bool ret = true;

	CharacterStateComponent* pStateComponent = pCharacterObj->GetStateComponent();
	if (pStateComponent != nullptr)
	{
		TRect<float> characterBB = pCharacterObj->BoundingBox();
		const GameObject::Direction characterDir = pCharacterObj->GetDirection();

		std::vector<LevelObject> lsCollisions;
		if (!objectBoundsTree.FindCollisions(characterBB, lsCollisions))
			pCharacterObj->TouchingGround(false);

		for (const auto& levelObj : lsCollisions)
		{
			const TRect<float>& levelObjBB  = levelObj.BoundingBox();
			const Collision::Side collision = pCharacterObj->GetCollisionSide(levelObjBB);

			if ((collision & Collision::Bottom) && (pCharacterObj->MovingDown() || pCharacterObj->IsStill()))
			{
				const float bottomDelta = characterBB.Bottom() - levelObjBB.Top();
				characterBB.MoveUp(bottomDelta);
				pCharacterObj->TouchingGround(true);
				pCharacterObj->SetYVelocity(0);
			}
			else if ((collision & Collision::Top) && (pCharacterObj->MovingUp() || pCharacterObj->IsStill()))
			{
				const float topDelta = levelObjBB.Bottom() - characterBB.Top();
				characterBB.MoveDown(topDelta);
				pCharacterObj->TouchingGround(false);
				pCharacterObj->SetYVelocity(0);
			}
			if ((collision & Collision::Left) && (pCharacterObj->MovingLeft() || pCharacterObj->IsStill()))
			{
				const float leftDelta = levelObjBB.Right() - characterBB.Left();
				pCharacterObj->TouchingGround(false);
				characterBB.MoveRight(leftDelta);
				pCharacterObj->SetXVelocity(0);
			}
			else if ((collision & Collision::Right) && (pCharacterObj->MovingRight() || pCharacterObj->IsStill()))
			{
				const float rightDelta = characterBB.Right() - levelObjBB.Left();
				pCharacterObj->TouchingGround(false);
				characterBB.MoveLeft(rightDelta);
				pCharacterObj->SetXVelocity(0);
			}
		}

		// Set new object position with collision resolved
		pCharacterObj->SetPosition(characterBB.TopLeft());
	}
	
	return ret;
}


