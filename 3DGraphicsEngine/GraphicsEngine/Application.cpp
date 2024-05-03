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
    const float t = timer.Peek();
    std::ostringstream oss;
    oss << "Time Elapsed: " << std::setprecision(1) << std::fixed << t << "s";
    wnd.SetTitle(oss.str());
}
