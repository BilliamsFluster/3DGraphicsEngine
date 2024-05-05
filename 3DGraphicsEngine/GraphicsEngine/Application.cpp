#include "Application.h"

Application::Application()
	:
	wnd(800, 600, "Graphics Engine")
{
}

int Application::Go()
{
    while (true)
    {
        if (const auto ecode = Window::ProcessMessages())
        {
            return *ecode;
        }
        DoFrame();
   }
    
}

void Application::DoFrame()
{
    const float c = sin(timer.Peek()) / 2 + 0.5f;
    wnd.Gfx().ClearBuffer(c, c, 1.0f);
    wnd.Gfx().EndFrame();
}
