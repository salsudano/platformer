#ifndef __GAME_OBJECT_DEFS_H
#define __GAME_OBJECT_DEFS_H

#define TEXTURE_FILE_EXT ".png"

namespace Collision
{
	enum Side
	{
		None        = (0),

		Left		= (1 << 0),
		Right		= (1 << 1),
		Top			= (1 << 2),
		Bottom		= (1 << 3),

		TopLeft     = (Top    |  Left),
		TopRight    = (Top    | Right),
		BottomLeft  = (Bottom |  Left),
		BottomRight = (Bottom | Right)
	};
};

#include "util\utils.h"
DECLARE_BITWISE_OPERATORS( Collision::Side );

struct ObjectTypes
{
	struct Character  
	{
		struct States 
		{
			enum IDs 
			{
				Standing,
				Crouching,
				Walking,
				Jumping,
				Falling
			};
		};
	};

	struct Interactive 
	{
		struct States 
		{
			enum IDs 
			{
				Still,
				Moving
			};
		};
	};

	struct Inactive
	{
		struct States 
		{
			enum IDs 
			{
				Still,
				Moving
			};
		};
	};
};


#endif // __GAME_OBJECT_DEFS_H