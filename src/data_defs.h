#ifndef __DATA_DEFS_H
#define __DATA_DEFS_H

struct GameData
{
	struct Menus
	{
		enum IDs
		{
			Title,
			Pause,
			Settings,
			Options
		};
	};

	struct Level
	{
		enum IDs
		{
			Test,
			One,
			Two,
			Three
		};
	};
};

#endif // __DATA_DEFS_H