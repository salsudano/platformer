#ifndef __MENU_DATA_H
#define __MENU_DATA_H

class MenuData
{
public:
			 MenuData();
	virtual ~MenuData();

	bool	Load()   { return false; }
	bool	Unload() { return false; }

	int		 ProcessInput()		 { return 0; }
	int		 Update()			 { return 0; }
	int		 UpdateGameObjects() { return 0; }

	bool IsActive() const { return m_bActive; }

private:
	bool m_bActive;

};

#endif // __MENU_DATA_H
