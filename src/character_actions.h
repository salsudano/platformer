#ifndef __CHARACTER_ACTIONS_H
#define __CHARACTER_ACTIONS_H

enum class ObjectAction
{
	Still,
	Moving
};

enum class CharacterAction
{
	None		=	   0,
	Stand		= 1 << 0,
	Crouch		= 1 << 1,
	MoveLeft	= 1 << 2,
	MoveRight	= 1 << 3,
	Run			= 1 << 4,
	Jump		= 1 << 5,
	Fall		= 1 << 6,
	Walk		= MoveLeft | MoveRight
};

#endif //__CHARACTER_ACTIONS_H