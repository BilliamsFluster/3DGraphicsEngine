#pragma once
#include "Window/Window.h"
#include "Core/Utils/Timer.h"
#include <memory>
#include "Core/DirectX/Box.h"


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
		std::vector<std::unique_ptr<class Box>> boxes;
};

