#include "character_controllable_states.h"

#include "level_data.h"
#include "character_object.h"
#include "physics_component.h"
#include "state_component.h"

bool ControllableCharacterStandingState::ProcessInput(CharacterObject* pCharacterObj)
{
	bool ret = true;

	auto pObjectState    = pCharacterObj->GetStateComponent();
	auto pInputComponent = pCharacterObj->GetInputComponent();
	if ((pObjectState != nullptr) && (pInputComponent != nullptr))
	{
		if (!pCharacterObj->TouchingGround())
			pObjectState->PushState(CharacterAction::Fall);
		else if (pInputComponent->InputDetectedForAction(CharacterAction::Jump) && pCharacterObj->CanJump())
			pObjectState->PushState(CharacterAction::Jump);
		else if (pInputComponent->InputDetectedForAction(CharacterAction::Crouch))
			pObjectState->PushState(CharacterAction::Crouch);
		else if (pInputComponent->InputDetectedForAction(CharacterAction::MoveLeft))
			pObjectState->PushState(CharacterAction::Walk);
		else if (pInputComponent->InputDetectedForAction(CharacterAction::MoveRight))
			pObjectState->PushState(CharacterAction::Walk);
		else
		{
			const float horzFriction = pCharacterObj->GetXFriction();
			const float minXVelocity = pCharacterObj->GetXVelocity(GameObject::Velocity::Min);
			const float curXVelocity = fabs(pCharacterObj->GetXVelocity());
			const float newXVelocity = (curXVelocity > minXVelocity) ? curXVelocity * horzFriction : 0;
			pCharacterObj->SetXVelocity(newXVelocity);
		}
	}

	return ret;
}

bool ControllableCharacterStandingState::Update(CharacterObject* pCharacterObj, LevelData* pLevelData)
{
	return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

bool ControllableCharacterWalkingState::ProcessInput(CharacterObject* pCharacterObj)
{
	bool ret = true;

	auto pInputComponent = pCharacterObj->GetInputComponent();
	if (pInputComponent != nullptr)
	{
		bool bMovingLeft  = pInputComponent->InputDetectedForAction(CharacterAction::MoveLeft);
		bool bMovingRight = pInputComponent->InputDetectedForAction(CharacterAction::MoveRight);

		const float xCurVelocity  = pCharacterObj->GetXVelocity(GameObject::Velocity::Current);
		const float xMinVelocity  = pCharacterObj->GetXVelocity(GameObject::Velocity::Min);
		const float xFriction	  = pCharacterObj->GetXFriction();
		const float xAcceleration = pCharacterObj->GetXAcceleration();

		if (bMovingLeft)
			pCharacterObj->SetXVelocity(xCurVelocity - xAcceleration);
		else if (bMovingRight)
			pCharacterObj->SetXVelocity(xCurVelocity + xAcceleration);
		else
			pCharacterObj->SetXVelocity(xCurVelocity * xFriction);

		if (pInputComponent->InputDetectedForAction(CharacterAction::Jump) && pCharacterObj->CanJump())
			pCharacterObj->GetStateComponent()->PushState(CharacterAction::Jump);
		else if (pInputComponent->InputDetectedForAction(CharacterAction::Crouch))
			pCharacterObj->GetStateComponent()->PushState(CharacterAction::Crouch);
	
		if (fabs(pCharacterObj->GetVelocity().x) < xMinVelocity)
			pCharacterObj->GetStateComponent()->PopState();
	}

	return ret;
}

bool ControllableCharacterWalkingState::Update(CharacterObject* pCharacterObj, LevelData* pLevelData)
{
	m_DistanceMoved.x += abs(m_LastPos.x - pCharacterObj->GetXPosition());
	if (m_DistanceMoved.x > MOVE_THRESHOLD)
	{
		SetNextTexture();
		m_DistanceMoved.x = 0;
	}

	m_LastPos = pCharacterObj->GetPosition();
	return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

bool ControllableCharacterCrouchingState::ProcessInput(CharacterObject* pCharacterObj)
{
	bool ret = true;

	auto pStateComponent = pCharacterObj->GetStateComponent();
	auto pInputComponent = pCharacterObj->GetInputComponent();
	if ((pStateComponent != nullptr) && (pInputComponent != nullptr))
	{
		if (pInputComponent->InputDetectedForAction(CharacterAction::Crouch))
		{
			const float xVelocity	 = pCharacterObj->GetXVelocity(GameObject::Velocity::Current);
			const float xMinVelocity = pCharacterObj->GetXVelocity(GameObject::Velocity::Min);
			const float xFriction	 = pCharacterObj->GetXFriction();
			const float newXVelocity = (fabs(xVelocity) > xMinVelocity) ? xVelocity * xFriction : 0.0f;
			pCharacterObj->SetXVelocity(newXVelocity);
		}
		else if (pInputComponent->InputDetectedForAction(CharacterAction::Jump) && pCharacterObj->CanJump())
		{
			pStateComponent->PushState(CharacterAction::Jump);
		}
		else if (pInputComponent->InputDetectedForAction(CharacterAction::MoveLeft) ||
			     pInputComponent->InputDetectedForAction(CharacterAction::MoveRight) )
		{
			pStateComponent->SwapCurrentState(CharacterAction::MoveLeft);
		}
		else
		{
			// Down has been released. Return to the last state
			pStateComponent->PopState();
		}
	}
	
	return ret;
}

bool ControllableCharacterCrouchingState::Update(CharacterObject* pCharacterObj, LevelData* pLevelData)
{
	return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

bool ControllableCharacterJumpingState::ProcessInput(CharacterObject* pCharacterObj)
{
	bool ret = true;

	auto pInputComponent = pCharacterObj->GetInputComponent();
	if (pInputComponent != nullptr)
	{
		const sf::Vector2<float>& velocity = pCharacterObj->GetVelocity();
		const sf::Vector2<float>& acceleration = pCharacterObj->GetAcceleration();

		if (pInputComponent->InputDetectedForAction(CharacterAction::MoveLeft))
			pCharacterObj->SetXVelocity(velocity.x - acceleration.x);
		if (pInputComponent->InputDetectedForAction(CharacterAction::MoveRight))
			pCharacterObj->SetXVelocity(velocity.x + acceleration.x);

		if (m_bFirstUpdate || (m_accelCount < 10 && pInputComponent->InputDetectedForAction(CharacterAction::Jump)))
			pCharacterObj->SetYVelocity(velocity.y - acceleration.y);
		else if (pCharacterObj->GetYVelocity() <= 0.0)
		{
			// We've reached the peak jump height
			pCharacterObj->GetStateComponent()->SwapCurrentState(CharacterAction::Fall);
		}
	}
	
	return ret;
}

bool ControllableCharacterJumpingState::Update(CharacterObject* pCharacterObj, LevelData* pLevelData)
{
	++m_accelCount;
	if (m_bFirstUpdate)
	{
		m_bFirstUpdate = false;
		m_OrigPosition = pCharacterObj->GetPosition();
		pCharacterObj->IncrementJumpCount();
	}

	return true;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

bool ControllableCharacterFallingState::ProcessInput(CharacterObject* pCharacterObj)
{
	bool ret = true;

	auto pInputComponent = pCharacterObj->GetInputComponent();
	if (pInputComponent != nullptr)
	{
		const float xVelocity = pCharacterObj->GetXVelocity();
		const float xAcceleration = pCharacterObj->GetXAcceleration();

		if (pInputComponent->InputDetectedForAction(CharacterAction::MoveLeft))
			pCharacterObj->SetXVelocity(xVelocity - xAcceleration);
		if (pInputComponent->InputDetectedForAction(CharacterAction::MoveRight))
			pCharacterObj->SetXVelocity(xVelocity + xAcceleration);
		if (pCharacterObj->TouchingGround())
			pCharacterObj->GetStateComponent()->PopState();
	}

	return ret;
}

bool ControllableCharacterFallingState::Update(CharacterObject* pCharacterObj, LevelData* pLevelData)
{
	if (m_bFirstUpdate)
	{
		m_bFirstUpdate = false;
		m_OrigPosition = pCharacterObj->GetPosition();
	}

	return true;
}
