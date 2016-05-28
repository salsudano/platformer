#include "character_object.h"
#include "character_states.h"
#include "level_data.h"

#include "state_component.h"
#include "physics_component.h"

CharacterObject::CharacterObject(const CharacterType type)
	: m_pStateComponent(nullptr)
	, m_pPhysicsComponent(nullptr)
	, m_pInputComponent(nullptr)
	, m_bCameraFocus(false)
	, m_bTouchingGround(false)
	, m_bCanJump(false)
	, m_JumpCount(0)
	, m_JumpLimit(2)
	, m_Type(type)
{
	this->SetDescription("character_object");
}

CharacterObject::~CharacterObject()
{
}

int CharacterObject::Update(LevelData* pLevelData)
{
	int ret = 0;
	
	CharacterAction currAction = CharacterAction::None;

	// update components
	if (m_pStateComponent != nullptr)
	{
		ret += m_pStateComponent->Update(this, pLevelData);
		currAction = m_pStateComponent->CurrentState()->Action();
	}
	if (m_pPhysicsComponent != nullptr)
		ret += m_pPhysicsComponent->Update(this, pLevelData);

	// update self
	m_bCanJump = (m_JumpCount < m_JumpLimit && currAction != CharacterAction::Jump);

	return ret;
}

int CharacterObject::Render(sf::RenderWindow& window)
{
	if (m_pStateComponent != nullptr)
	{
		sf::Sprite* pSprite = m_pStateComponent->CurrentSprite();
		if (pSprite != nullptr)
		{
			const Direction xdir = this->GetXDirection();

			if (xdir == Direction::Right)
			{
				pSprite->setScale(1, 1);
				pSprite->setPosition(m_Position);
			}
			else
			{
				TPoint<float> drawPos = m_Position;
				drawPos.x += pSprite->getTextureRect().width;
				pSprite->setScale(-1, 1);
				pSprite->setPosition(drawPos);
			}

			window.draw(*pSprite);
		}
	}
	return 0;
}

bool CharacterObject::HasComponent(Component::Type type) const
{
	switch (type)
	{
		case Component::Type::State:
			return (m_pStateComponent != nullptr);
		case Component::Type::Physics:
			return (m_pPhysicsComponent != nullptr);
	}
	return false;
}

CharacterStateComponent* CharacterObject::GetStateComponent()
{
	return m_pStateComponent;
}

const CharacterStateComponent* CharacterObject::GetStateComponent() const
{
	return m_pStateComponent;
}

void CharacterObject::SetStateComponent(CharacterStateComponent* pStateComponent)
{
	assert(m_pStateComponent == nullptr);
	m_pStateComponent = pStateComponent;
}
	
PhysicsComponent* CharacterObject::GetPhysicsComponent()
{
	return m_pPhysicsComponent;
}

const PhysicsComponent* CharacterObject::GetPhysicsComponent() const
{
	return m_pPhysicsComponent;
}

void CharacterObject::SetPhysicsComponent(PhysicsComponent* pPhysicsComponent)
{
	assert(m_pPhysicsComponent == nullptr);
	m_pPhysicsComponent = pPhysicsComponent;
}

CharacterInputComponent* CharacterObject::GetInputComponent()
{
	return m_pInputComponent;
}

const CharacterInputComponent* CharacterObject::GetInputComponent() const
{
	return m_pInputComponent;
}

void CharacterObject::SetInputComponent(CharacterInputComponent* pInputComponent)
{
	assert(m_pInputComponent == nullptr);
	m_pInputComponent = pInputComponent;
}

int CharacterObject::IncrementJumpCount()
{
	return ++m_JumpCount;
}

bool CharacterObject::CanJump() const
{
	return m_bCanJump;
}

bool CharacterObject::CameraFocus() const
{
	return m_bCameraFocus;
}

void CharacterObject::CameraFocus(bool bFocus)
{
	m_bCameraFocus = bFocus;
}

void CharacterObject::TouchingGround(bool bTouchingGround)
{
	m_bTouchingGround = bTouchingGround;
	if (bTouchingGround)
		m_JumpCount = 0;
}

bool CharacterObject::TouchingGround() const
{
	return m_bTouchingGround;
}

CharacterType CharacterObject::Type() const
{
	return m_Type;
}

void CharacterObject::SetPosition(const TPoint<float>& pos)
{
	this->SetPosition(pos.x, pos.y);
}

void CharacterObject::SetPosition(const float x, const float y)
{
	GameObject::SetPosition(x, y);
	if (m_pStateComponent != nullptr)
		m_pStateComponent->CurrentSprite()->setPosition(m_Position);
}

Collision::Side CharacterObject::GetCollisionSide(const TRect<float>& thatBB) const
{
	Collision::Side collision = Collision::None;

	const TRect<float>& thisBB = this->BoundingBox();
	const TRect<float>  intersection = thisBB.Intersection(thatBB);

	if (intersection.Width() < intersection.Height())
	{
		if (intersection.Left() == thisBB.Left())
			collision |= Collision::Left;
		if (intersection.Right() == thisBB.Right())
			collision |= Collision::Right;
	}
	else if (intersection.Height() <= intersection.Width())
	{
		if (intersection.Top() == thisBB.Top())
			collision |= Collision::Top;
		if (intersection.Bottom() == thisBB.Bottom())
			collision |= Collision::Bottom;
	}

	return collision;
}

TRect<float> CharacterObject::BoundingBox() const
{
	TRect<float> boundingBox(m_Position, 0, 0);
	if (m_pStateComponent != nullptr)
	{
		const sf::Sprite* pCurrSprite = m_pStateComponent->CurrentSprite();
		if (pCurrSprite != nullptr)
		{
			const sf::IntRect& textureRect = pCurrSprite->getTextureRect();
			boundingBox.SetHeight(static_cast<float>(textureRect.height));
			boundingBox.SetWidth(static_cast<float>(textureRect.width));
		}
	}
	return boundingBox;
}

sf::RectangleShape CharacterObject::BoundingRectShape() const
{
	sf::RectangleShape spriteRect;
	if (m_pStateComponent != nullptr)
	{
		const sf::Sprite* pCurrSprite = m_pStateComponent->CurrentSprite();
		if (pCurrSprite != nullptr)
		{
			const sf::IntRect& textureRect = pCurrSprite->getTextureRect();
			TPoint<float> spriteRectSize(fabs(static_cast<float>(textureRect.width)), fabs(static_cast<float>(textureRect.height)));
			spriteRect.setSize(spriteRectSize);
			spriteRect.setFillColor(sf::Color::Transparent);
			spriteRect.setOutlineColor(sf::Color::Red);
			spriteRect.setOutlineThickness(10);
			spriteRect.setPosition(m_Position);
		}
	}
	return spriteRect;
}
