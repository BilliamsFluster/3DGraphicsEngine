#pragma once
#include "Window/Window.h"
#include "Core/Utils/Timer.h"


class Application
{
public: 
	Application();
	int Go();
private:
	void DoFrame();
private:
		Window wnd;
		Utils::Timer timer;
};

