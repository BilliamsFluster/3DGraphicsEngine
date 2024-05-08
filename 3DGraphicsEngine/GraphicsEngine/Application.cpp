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
    wnd.Gfx().DrawTestTriangle(timer.Peek(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f);
    wnd.Gfx().DrawTestTriangle(timer.Peek(),0 / 400.0f - 1.0f,0 / 300.0f + 1.0f);
    wnd.Gfx().EndFrame();
}
