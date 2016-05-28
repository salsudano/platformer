#include "application.h"

Application::Application(const sf::String& title)
	: m_Settings(title)
	, m_Log(title.toAnsiString())
	, m_GraphicsMgr(m_MainWindow)
	, m_WindowEventMgr()
	, m_pData(nullptr)
{
	m_MainWindow.create(m_Settings.Display.Resolution(), title);
}

Application::~Application()
{
}

bool Application::ShouldExit()
{
	bool bRet = !m_MainWindow.isOpen();
	return bRet;
}
