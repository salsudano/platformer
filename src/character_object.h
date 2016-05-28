#ifndef __CHARACTER_OBJECT_H
#define __CHARACTER_OBJECT_H

#include "game_object.h"

#include "physics_component.h"
#include "character_state_component.h"
#include "character_input_component.h"

#include "character_actions.h"
#include "character_ai_states.h"
#include "character_controllable_states.h"

enum class CharacterType
{
	Controllable,
	AI
};

enum class AIType
{
	Friend,
	Enemy
};

class CharacterObject : public GameObject
{
public:
										CharacterObject(const CharacterType type);
	virtual							   ~CharacterObject();

	virtual int							ProcessInput() = 0;
	virtual int							Update(LevelData* pLevelData);
	virtual int							Render(sf::RenderWindow& window);

	void								SetPosition(const TPoint<float>& pos);
	void								SetPosition(const float x, const float y) override final;

	TRect<float>						BoundingBox()		const override;
	sf::RectangleShape					BoundingRectShape() const;

	bool								HasComponent(Component::Type type) const;

	CharacterStateComponent*			GetStateComponent();
	const CharacterStateComponent*		GetStateComponent() const;
	void								SetStateComponent(CharacterStateComponent* pStateComponent);
	
	PhysicsComponent*					GetPhysicsComponent();
	const PhysicsComponent*				GetPhysicsComponent() const;
	void								SetPhysicsComponent(PhysicsComponent* pPhysicsComponent);

	CharacterInputComponent*			GetInputComponent();
	const CharacterInputComponent*		GetInputComponent() const;
	void								SetInputComponent(CharacterInputComponent* pInputComponent);

	bool								TouchingGround() const;
	void								TouchingGround(bool bTouchingGround);

	bool								CameraFocus() const;
	void								CameraFocus(bool bFocus);
	
	Collision::Side						GetCollisionSide(const TRect<float>& rect) const;

	bool								CanJump() const;
	int									IncrementJumpCount();

	CharacterType						Type()	  const;

protected:
	PhysicsComponent*					m_pPhysicsComponent; 
	CharacterStateComponent*			m_pStateComponent;
	CharacterInputComponent*			m_pInputComponent;

private:
	bool					m_bCameraFocus;
	bool					m_bTouchingGround;
	bool					m_bCanJump;
	int					    m_JumpCount;
	int						m_JumpLimit;
	CharacterType			m_Type;
};

class ControllableCharacter : public CharacterObject
{
public:
	ControllableCharacter() 
		: CharacterObject(CharacterType::Controllable)
	{
		this->CameraFocus(true);
		this->SetPosition(75, 75);
		this->SetDescription("Controllable_Character");

		// default character components
		this->SetPhysicsComponent(new PhysicsComponent());
		this->SetStateComponent(new CharacterStateComponent());
		this->SetInputComponent(new CharacterInputComponent());
	}

	~ControllableCharacter() 
	{
	}

	virtual int ProcessInput() override
	{
		if (m_pStateComponent != nullptr) 
		{
			CharacterState* pCharacterState = m_pStateComponent->CurrentState();
			assert(pCharacterState != nullptr);
			pCharacterState->ProcessInput(this);
		}
		return 0;
	}
};

class AICharacter : public CharacterObject
{
public:
	AICharacter() 
		: CharacterObject(CharacterType::AI) 
	{
		this->SetDescription("AI_Character");

		// default character components
		this->SetPhysicsComponent(new PhysicsComponent());
		this->SetStateComponent(new CharacterStateComponent());
	}

	~AICharacter() 
	{
	}
};

#endif // __CHARACTER_OBJECT_H